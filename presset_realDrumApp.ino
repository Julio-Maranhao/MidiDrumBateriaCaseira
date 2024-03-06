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

  Pin[0].set(A0, "HH Control2", 54, 1);
  Pin[0].minSens = 300;
  Pin[0].maxSens = 900;

  Pin[1].set(A1, "None1", 4, 0, true);
  Pin[2].set(A2, "None1", 4, 0, true);

  Pin[3].set(A3, "Snare", 51, 0);
  Pin[3].minSens = 300;
  Pin[3].maxSens = 900;

  Pin[4].set(A4, "None2", 38, 0, true);

  Pin[5].set(A5, "Crash", 61, 0);
  Pin[5].minSens = 300;
  Pin[5].maxSens = 900;

  Pin[6].set(A6, "None3", 4, 0, true);

  Pin[7].set(A7, "Hihat", 54, 0);
  Pin[7].minSens = 300;
  Pin[7].maxSens = 900;

  Pin[8].set(A8, "None4", 4, 0, true);

  Pin[9].set(A9, "Kick", 72, 0);
  Pin[9].minSens = 300;
  Pin[9].maxSens = 900;

  Pin[10].set(A10, "Ride", 63, 0);
  Pin[10].minSens = 300;
  Pin[10].maxSens = 900;

  Pin[11].set(A11, "Tom", 53, 0);
  Pin[11].minSens = 300;
  Pin[11].maxSens = 900;

  Pin[12].set(A12, "Floor", 71, 0);
  Pin[12].minSens = 300;
  Pin[12].maxSens = 900;

  Dpin[0].set(22, "Choke", 64, 0);
  Dpin[1].set(23, "None", 87, 0, true);
}
