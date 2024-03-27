void addictiveDrums(){
  midiChannel = 1;                    
  hhControlSens = 1;                  
  hhPin = 7;                             
  hhControlPin = 0;                       
  hhControlMode = true;                  
  hhControlType = true;                  
  hhControlStages = 3;                    
  hhNote1 = 46;                           
  hhNote2 = 44;                           
  hhNote3 = 42;   

  Pin[0].set(A0, "HH Control", 4, 1);
  Pin[1].set(A1, "Ride", 60, 0, true);
  Pin[2].set(A2, "Bell", 61, 0, true);
  Pin[3].set(A1, "Snare", 38, 0);
  Pin[4].set(A2, "Rim", 42, 0, true);
  Pin[5].set(A5, "Crash1", 77, 0);
  Pin[6].set(A6, "Crash2", 79, 0, true);
  Pin[7].set(A7, "Hihat", 49, 0);
  Pin[8].set(A8, "Splash", 81, 0, true);
  Pin[9].set(A9, "Kick", 36, 0);
  Pin[10].set(A10, "Tom1", 71, 0);
  Pin[11].set(A11, "Tom2", 69, 0);
  Pin[12].set(A12, "Floor", 65, 0);

  Dpin[0].set(22, "Choke1", 78, 0, true);
  Dpin[1].set(23, "Choke2", 80, 0, true);
}