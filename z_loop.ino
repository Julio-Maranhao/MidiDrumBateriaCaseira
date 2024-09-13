void loop() {
  // mechanical HH Control
  byte hhNoteIndex;
  if (! hhControlMode){
    if(hhControlType){
      hhNoteIndex = Pin[hhControlPin].playHHMechanicalControl();
    } else {
      hhNoteIndex = Dpin[hhControlPin].playHHMechanicalControl();
    }
    switch (hhNoteIndex) {
      case 1:
        Pin[hhPin].note = hhNote1;
        break;
      case 2:
        if (hhControlStages == 2){
          Pin[hhPin].note = hhNote3;
        } else {
          Pin[hhPin].note = hhNote2;
        }
        break;
      case 3:
        Pin[hhPin].note = hhNote3;
        break;
      default:
        break;
    }
  }

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
    // jump mechanical HH control
    if (! hhControlMode && hhControlType && i == hhControlPin) {continue;}
    Pin[i].playMIDI();
    if (Pin[i].state == Scan_Time) {
      Pin[i].playMIDI();
      Pin[i].playMIDI();
      Pin[i].playMIDI();
    }
  }
  for(int i = 0; i<DIGITALPINS; i++){
    // jump mechanical HH control
    if (! hhControlMode && ! hhControlType && i == hhControlPin) {continue;}
    Dpin[i].playMIDI();
  }

  // delay to mantain stable
  //delay(1);
}