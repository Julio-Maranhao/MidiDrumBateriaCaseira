void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(CIMA)){
    handler.pushOnTop("CIMA");
    handler.indicatePosition(0);
  }
  if(!digitalRead(BAIXO)){
    handler.pushOnBottom("BAIXO");
    handler.indicatePosition(3);
  }
  /*lcdMessage x = Pin[0].Scan();
  if(x.trigger){
    handler.replaceValue(1, x.pinName);
    handler.replaceValue(2, x.pinNote);
    handler.replaceValue(3, x.pinVelocity);
  }*/
  delay(4);
  /*for (int button : buttons) {
    if(!digitalRead(button)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hello World");
      lcd.setCursor(0,1);
      lcd.print(button);
      maxPin = 0;
      delay(10);
    }
  }

  lcd.setCursor(0,2);
  lcd.print(analogPin.Scan());
  analogPin.setNome("chama 2");
  lcd.setCursor(0,3);
  lcd.print(analogPin.Scan());
  delay(200);*/

}