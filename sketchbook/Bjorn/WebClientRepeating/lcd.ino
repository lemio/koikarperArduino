void lcdDisplay(){
  lcdButtonControl();
  lcdMenu();
  lcdEditValues();
}
void lcdButtonControl(){
  ValUp=digitalRead(buttonPinUp);//Item 1 keer opschuiven naar volgend item

  if (ValUp !=LastValUp){
    if (ValUp==HIGH){
      lcdItem++;
    }
  }

  LastValUp=ValUp;

  ValDown=digitalRead(buttonPinDown);//Item 1 keer terug schuiven naar volgend item

  if (ValDown !=LastValDown){
    if (ValDown==HIGH){
      lcdItem--;
    }
  }
  LastValDown=ValDown;
}
void lcdMenu(){
  switch (lcdItem){ // Display items
  case 0:
    lcd.clear();
    lcd.setCursor(0,0);//regel boven
    if (autoEnabled){
      lcd.print("Auto");
    }
    else{
      lcd.print("Manual");
    }
    lcd.print(ReadTimeDate());
    lcd.setCursor(0,1);// regel onder 
    lcd.print("T"); 
    lcd.print(temp,1);
    lcd.print(" C");// wat wordt weer gegeven in het scherm
    break;
  case 1:
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print ("Time feeder 1");
    break;
  case 2:
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print ("Time feeder 2");
    break;
  case 3:
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print ("Time feeder 3");
    break;
  case 4:
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print ("Weight of feeding");
    break;
  case 5:
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print ("Speed spreader");
    lcd.setCursor(0,1);// regel onder
    lcd.print(speedSpreader);
    break;
  case 6:
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print ("Set time");
    break;
  case 7:
    lcd.clear();
    lcd.setCursor (0,0); 
    lcd.print ("Set date");
    break;
  case 8:
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print ("Sample run");
    break;
  }
  lcdItem = constrain(lcdItem, 0, 8);
}
void lcdEditValues(){

}
