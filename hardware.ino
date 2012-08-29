//The function to feed the fishes
void fishesFeed(unsigned int number){
  Serial.print("Fishes get ");
  Serial.print(number);
  Serial.print(" amount of food.");
}
float getTemp(){
  int val= analogRead(tempSensor); // Temperatuur lezen van sensor
  return (val*0.0048828125-1.375)/0.0225;
}
