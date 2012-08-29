/*
@author  Geert Roumen (Lemio)
 @license Creative Commons 
 Attribution-NonCommercial-ShareAlike 
 3.0 Unported
 @git     https://github.com/lemio/koikarperArduino
 @name    Koikarper Feeding system
 
 description
 ---

 */
//#include <Wire.h> 
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>

byte timeId = 0;
//Up, down and UpDown chars

byte lcdCharUpDown[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b00000,
  0b11111,
  0b01110,
  0b00100
};

//Analog temp sensor pin.
const byte tempSensor = A1;

//Temp value in C
float temp = 0;

//LCD control button pins.
const byte buttonPinUp = A4;      // pin for the Up button
const byte buttonPinDown = A3;    // pin for the Down button
const byte buttonPinEsc = A1;     // pin for the Esc button
const byte buttonPinEnter = A2;   // pin for the Enter button

//LCD control button values.
boolean LastValUp = true;
boolean LastValDown = true;
boolean LastValEsc = true;
boolean LastValEnter = true;

//Speed values
int speedSpreader = 0;

//Weight values
int feedingWeight = 0;
//Timer values
boolean timeEnabled[] = {false,false,false};
int timeHours[] = {0,0,0};
int timeMinutes[] = {0,0,0};

//LCD item
int lcdItem = 0;

int lcdEdit = 0;

//Online auto-feed system enabled.
boolean autoEnabled = true;

//Real time clock values
const int  spiRtc=8; //chip select 
const int  spiEthernet = 10;
const char* VERSION = "0.0.1";

//LCD init
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Ethernet values
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

EthernetClient client;

//The server to connect to.
IPAddress server(159,253,0,21);
unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 20*1000;  // delay between updates, in milliseconds

void setup() {
  pinMode(buttonPinUp, INPUT);
  digitalWrite(buttonPinUp, HIGH);
  pinMode(buttonPinDown, INPUT);
  digitalWrite(buttonPinDown, HIGH);
  pinMode(buttonPinEnter, INPUT);
  digitalWrite(buttonPinEnter, HIGH);
  pinMode(buttonPinEsc, INPUT);
  digitalWrite(buttonPinEsc, HIGH);
  //Disable RTC by default.
  pinMode(spiRtc,OUTPUT);
  digitalWrite(spiRtc,HIGH);
      lcd.createChar(0, lcdCharUpDown);
  lcd.begin(16, 2);

  // Print a message to the LCD.
  //lcd.backlight();
  //lcd.print("Hello, world!");
  //init the realtimeclock
  RTC_init();
  // start serial port:
  Serial.begin(9600);
  // give the ethernet module time to boot up:
  delay(1000);
 
  // start the Ethernet connection using a fixed IP address and DNS server:
  lcd.print("Connecting...");
  Ethernet.begin(mac);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  lcd.clear();
  lcd.print("Connected");

}

void loop() {

  
  temp = getTemp();
  //Get the data from the server, and use it.
  if (autoEnabled){
    char command = fetchData();
    switch (command) {
    case 'A':
      //Feed the fishes
      fishesFeed(256*client.read()+client.read());
      break;
    case 'B':
      //Set the RTC time
      SetTimeDate(client.read() - 'A', client.read() - 'A', 256*client.read()+client.read(), client.read() - 'A', client.read() - 'A', client.read() - 'A');
      break;
    case 'C':
      //Optional
      break;
    case 'D':
      //Error
      break;
    }
    //Check if the connection is stopped.
    checkConnection();
    //When it is time to connect the server, connect it and send some values to the server.
    if(isConnectionTime()) {
      httpRequest(analogRead(0),timeHours[0]*100 + timeMinutes[0],timeHours[1]*100 + timeMinutes[1],timeHours[2]*100 +  timeMinutes[2],0);
    }
    //Store the state of the connection for next time.
    lastConnected = client.connected();
  }
  if (!lastConnected || !autoEnabled){
    lcdDisplay();
  }
  
}








