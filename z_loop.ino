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
  Pin[0].scan();
  delay(4);
}