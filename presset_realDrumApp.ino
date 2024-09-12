// presset for Real Drums APP from Kolb APPS
void realDrum(){
  midiChannel = 1;                    
  hhControlSens = 1;                  
  hhPin = 7;                             
  hhControlPin = 0;                       
  hhControlMode = false;                  
  hhControlType = true;                  
  hhControlStages = 2;                    
  hhNote1 = 58;                           
  hhNote2 = 56;                           
  hhNote3 = 54;   

  Pin[0].set(A0, "HH Control", 54, 1);
  Pin[1].set(A1, "Ride", 63, 0, true);
  Pin[2].set(A2, "Bell", 65, 0, true);
  Pin[3].set(A1, "Snare", 51, 0);
  Pin[4].set(A2, "Rim", 53, 0, true);

  Pin[5].set(A5, "Crash1", 61, 0);
  Pin[6].set(A6, "Crash2", 67, 0, true);
  Pin[7].set(A7, "Hihat", 54, 0);
  Pin[8].set(A8, "Splash", 64, 0, true);
  Pin[9].set(A9, "Kick", 72, 0);
  Pin[10].set(A10, "Tom1", 57, 0);
  Pin[11].set(A11, "Tom2", 60, 0);
  Pin[12].set(A11, "Floor", 71, 0);

  Dpin[0].set(22, "Choke1", 64, 0, true);
  Dpin[1].set(23, "Choke2", 60, 0, true);
}
