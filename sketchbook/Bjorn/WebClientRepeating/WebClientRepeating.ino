//#include <Wire.h> 
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>

//Analog temp sensor pin.
const byte tempSensor = A1;

//Temp value in C
float temp = 0;

//LCD control button pins.
const byte buttonPinUp = 3;      // pin for the Up button
const byte buttonPinDown = 2;    // pin for the Down button
const byte buttonPinEsc = 9;     // pin for the Esc button
const byte buttonPinEnter = 10;   // pin for the Enter button

//LCD control button values.
int ValUp = 0; 
int LastValUp = 0;
int ValDown = 0; 
int LastValDown = 0;

//Speed values
int speedSpreader = 0;

//LCD item
byte lcdItem = 0;

//Online auto-feed system enabled.
boolean autoEnabled = true;

//Real time clock values
const int  cs=8; //chip select 
const char* VERSION = "0.0.1";

//LCD init
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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
  Ethernet.begin(mac);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
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
      SetTimeDate(client.read() - 'A', client.read() - 'A', 256*client.read()*client.read(), client.read() - 'A', client.read() - 'A', client.read() - 'A');
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
      httpRequest(analogRead(0),analogRead(1),analogRead(2),analogRead(3),analogRead(4));
    }
    //Store the state of the connection for next time.
    lastConnected = client.connected();
  }
  if (!lastConnected || !autoEnabled){
    lcdDisplay();
  }
}








