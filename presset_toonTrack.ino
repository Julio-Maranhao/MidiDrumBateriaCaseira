void toontrack(){
  midiChannel = 1;                    
  hhControlSens = 1;                  
  hhPin = 7;                             
  hhControlPin = 0;                       
  hhControlMode = true;                  
  hhControlType = true;                  
  hhControlStages = 3;                    
  hhNote1 = 60;                           
  hhNote2 = 25;                           
  hhNote3 = 22;   

  Pin[0].set(A0, "HH Control", 4, 1);
  Pin[1].set(A1, "Ride", 51, 0, true);
  Pin[2].set(A2, "Bell", 53, 0, true);
  Pin[3].set(A1, "Snare", 38, 0);
  Pin[4].set(A2, "Rim", 37, 0, true);
  Pin[5].set(A5, "Crash1", 55, 0);
  Pin[6].set(A6, "Crash2", 57, 0, true);
  Pin[7].set(A7, "Hihat", 22, 0);
  Pin[8].set(A8, "Splash", 51, 0, true);
  Pin[9].set(A9, "Kick", 36, 0);
  Pin[10].set(A10, "Tom1", 81, 0);
  Pin[11].set(A11, "Tom2", 79, 0);
  Pin[12].set(A11, "Floor", 72, 0);

  Dpin[0].set(22, "Choke1", 54, 0, true);
  Dpin[1].set(23, "Choke2", 58, 0, true);
}