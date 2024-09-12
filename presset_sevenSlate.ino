void sevenSlate(){
  midiChannel = 1;                    
  hhControlSens = 1;                  
  hhPin = 7;                             
  hhControlPin = 0;                       
  hhControlMode = true;                  
  hhControlType = true;                  
  hhControlStages = 3;                    
  hhNote1 = 71;                           
  hhNote2 = 69;                           
  hhNote3 = 67;   

  Pin[0].set(A0, "HH Control", 4, 1);
  Pin[1].set(A1, "Ride", 59, 0, true);
  Pin[2].set(A2, "Bell", 53, 0, true);
  Pin[3].set(A1, "Snare", 38, 0);
  Pin[4].set(A2, "Rim", 37, 0, true);
  Pin[5].set(A5, "Crash1", 55, 0);
  Pin[6].set(A6, "Crash2", 57, 0, true);
  Pin[7].set(A7, "Hihat", 67, 0);
  Pin[8].set(A8, "Splash", 50, 0, true);
  Pin[9].set(A9, "Kick", 36, 0);
  Pin[10].set(A10, "Tom1", 48, 0);
  Pin[11].set(A11, "Tom2", 47, 0);
  Pin[12].set(A11, "Floor", 41, 0);

  Dpin[0].set(22, "Choke1", 54, 0, true);
  Dpin[1].set(23, "Choke2", 56, 0, true);
}