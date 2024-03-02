void loop() {
  // put your main code here, to run repeatedly:
  // Read Control Buttons
  Buttons[0].readButton();
  Buttons[1].readButton();
  Buttons[2].readButton();
  Buttons[3].readButton();
  Buttons[4].readButton();
  
  //Navigate Main Menu
  mainMenu.navigate();

  // Scan all pins
  for(int i = 0; i<ANALOGPINS; i++){
    Pin[i].playMIDI();
  }

  delay(1);
}