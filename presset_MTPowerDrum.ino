// presset for MT Power Drum 2
void powerDrum(){
  midiChannel = 1;                    
  hhControlSens = 1;                  
  hhPin = 7;                             
  hhControlPin = 0;                       
  hhControlMode = false;                  
  hhControlType = true;                  
  hhControlStages = 3;                    
  hhNote1 = 46;                           
  hhNote2 = 44;                           
  hhNote3 = 42;   

  Pin[0].set(A0, "HH Control", 42, 1);
  Pin[0].minSens = 300;
  Pin[0].maxSens = 900;
  Pin[1].set(A1, "Ride", 51, 0, true);
  Pin[1].minSens = 300;
  Pin[1].maxSens = 900;
  Pin[2].set(A2, "Bell", 53, 0, true);
  Pin[2].minSens = 300;
  Pin[2].maxSens = 900;
  Pin[3].set(A1, "Snare", 38, 0);
  Pin[3].minSens = 300;
  Pin[3].maxSens = 900;
  Pin[4].set(A2, "Rim", 37, 0, true);
  Pin[4].minSens = 300;
  Pin[4].maxSens = 900;

  Pin[5].set(A5, "Crash1", 49, 0);
  Pin[5].minSens = 300;
  Pin[5].maxSens = 900;
  Pin[6].set(A6, "Crash2", 57, 0, true);
  Pin[6].minSens = 300;
  Pin[6].maxSens = 900;
  Pin[7].set(A7, "Hihat", 42, 0);
  Pin[7].minSens = 300;
  Pin[7].maxSens = 900;
  Pin[8].set(A8, "Splash", 52, 0, true);
  Pin[8].minSens = 300;
  Pin[8].maxSens = 900;
  Pin[9].set(A9, "Kick", 36, 0);
  Pin[9].minSens = 300;
  Pin[9].maxSens = 900;
  Pin[10].set(A10, "Tom1", 48, 0);
  Pin[10].minSens = 300;
  Pin[10].maxSens = 900;
  Pin[11].set(A11, "Tom2", 45, 0);
  Pin[11].minSens = 300;
  Pin[11].maxSens = 900;
  Pin[12].set(A12, "Floor", 41, 0);
  Pin[12].minSens = 300;
  Pin[12].maxSens = 900;

  Dpin[0].set(22, "Choke1", 84, 0, true);
  Dpin[0].defaultState = true;
  Dpin[1].set(23, "Choke2", 58, 0, true);
  Dpin[1].defaultState = true;
}