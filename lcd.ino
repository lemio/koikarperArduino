void lcdDisplay(){
  Serial.print("LCDedit: ");
  Serial.println(lcdEdit);
  if (lcdEdit == 0){
    lcdItem = loopConstrain(lcdUpDownControl(lcdItem),0,8);//constrain(, 0, 8);//
    Serial.print("LCDitem: ");
    
  Serial.println(lcdItem);
  }
  lcdButtonControl();
  lcdMenu();
  lcdEditValues();
}
void lcdButtonControl(){
  boolean ValEnter=digitalRead(buttonPinEnter);//Item 1 keer opschuiven naar volgend item

  if (ValEnter !=LastValEnter){
    if (ValEnter==LOW){
      Serial.print("ENTER");
      lcd.clear();
      lcdEdit ++;
    }
  }

  LastValEnter=ValEnter;
  boolean ValEsc=digitalRead(buttonPinEsc);//Item 1 keer opschuiven naar volgend item

  if (ValEsc !=LastValEsc){
    if (ValEsc==LOW){
      lcd.clear();
      lcdEdit = 0;
    }
  }

  LastValEsc=ValEsc;
}
boolean lcdUpDownControl(int oldValue){
  boolean ValUp=digitalRead(buttonPinUp);//Item 1 keer opschuiven naar volgend item


  if (ValUp !=LastValUp){
    if (ValUp==LOW){
       Serial.println("plus");
         LastValUp=ValUp;
         lcd.clear();
      return oldValue + 1;
    }
  }

  LastValUp=ValUp;
  

  boolean ValDown=digitalRead(buttonPinDown);//Item 1 keer terug schuiven naar volgend item

  if (ValDown !=LastValDown){
    if (ValDown==LOW){
        LastValDown=ValDown;
        lcd.clear();
        
          return oldValue - 1;
        
    }
  }
  LastValDown=ValDown;
  return oldValue;
}
void lcdMenu(){
  switch (lcdItem){ // Display items
  case 0:

    lcd.setCursor(0,0);//regel boven
    if (autoEnabled){
      lcd.print("A ");
    }
    else{
      lcd.print("M ");
    }
    lcd.print(ReadTimeDate());
    lcd.setCursor(0,1);// regel onder 
    lcd.print("T"); 
    lcd.print(temp);
    lcd.print(" C      ");// wat wordt weer gegeven in het scherm
    delay(10);
    break;
  case 1:

    lcd.setCursor (0,0);
    lcd.print ("Time feeder 1");
    break;
  case 2:

    lcd.setCursor (0,0);
    lcd.print ("Time feeder 2");
    break;
  case 3:

    lcd.setCursor (0,0);
    lcd.print ("Time feeder 3");
    break;
  case 4:

    lcd.setCursor (0,0);
    lcd.print ("Weight feeding");
    break;
  case 5:

    lcd.setCursor (0,0);
    lcd.print ("Speed spreader");
    break;
  case 6:

    lcd.setCursor (0,0);
    lcd.print ("Set time");
    break;
  case 7:

    lcd.setCursor (0,0); 
    lcd.print ("Set date");
    break;
  case 8:

    lcd.setCursor (0,0);
    lcd.print ("Sample run");
    break;
  }
}
void lcdEditValues(){
  
  byte timeId = 0;
  lcd.setCursor (0,1); 
  switch(lcdItem){
  case 0:
  lcdEdit = 0;
  break;
  case 1:
  case 2:
  case 3:
    timeId = lcdItem-1;
    if (timeEnabled[timeId]){
      lcd.print("on");
    }
    else{
      lcd.print("off");
    }
    if (lcdEdit == 1){
      lcd.print('\x00');
      timeEnabled[timeId] = loopConstrain(lcdUpDownControl(timeEnabled[timeId]), 0, 1);
    }
    else{
      lcd.print(" ");
    }
    lcd.print(timeHours[timeId]);
    if (lcdEdit == 2){
      lcd.print('\x00');
      timeHours[timeId] = loopConstrain(lcdUpDownControl(timeHours[timeId]),0,23);//constrain(, 0, 23);
    }
    else{
      lcd.print(" ");
    }
    lcd.print(":");
    lcd.print(timeMinutes[timeId]);
    if (lcdEdit == 3){
      lcd.print('\x00');
      timeMinutes[timeId] = loopConstrain(lcdUpDownControl(timeMinutes[timeId]), 0, 59);
    }
    else{
      lcd.print(" ");
    }
    if (lcdEdit == 4){
      lcdEdit = 0;
    }
    break;
   case 4:
    lcd.print(feedingWeight);
    if (lcdEdit == 1){
      Serial.print("Edit mode");
      lcd.print('\x00');
      feedingWeight = loopConstrain(lcdUpDownControl(feedingWeight), 0, 1000);
    }
    if (lcdEdit == 2){
      lcdEdit = 0;
    }
    break;
    case 5:
    lcd.print(speedSpreader);
    if (lcdEdit == 1){
      lcd.print('\x00');
      speedSpreader = loopConstrain(lcdUpDownControl(speedSpreader), 0, 1000);
    }
    if (lcdEdit == 2){
      lcdEdit = 0;
    }
    break;
    case 6:
    lcd.print("disabled");
    if (lcdEdit == 2){
      lcdEdit = 0;
    }
    break;
    case 7:
    lcd.print("disabled");
    if (lcdEdit == 2){
      lcdEdit = 0;
    }
    break;
    case 8:
    lcd.print("Press enter to run");
    if (lcdEdit == 1){
      lcdEdit = 0;
    }
    break;
  }
}

int loopConstrain(int x,int a,int b){
 if (x == a-1 || x == 255){
   return b;
 }
 if (x == b+1){
   return a;
 }
}
