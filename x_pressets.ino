String getPresset(int num){
  switch(num) {
    case 0:
      return "Default";
      break;
    case 1:
      return "Real Drums APP";
      break;
    default:
      return "--------------------";
  }
}

void setPresset(int num){
  switch(num) {
    case 0:
      defaultPresset();
      break;
    case 1:
      realDrum();
      break;
    default:
      return;
  }
}

void defaultPresset(){
  Pin[0].set(A0, "HH Control", 4, 1);
  Pin[1].set(A1, "None", 4, 0, true);
  Pin[2].set(A2, "None", 4, 0, true);
  Pin[3].set(A3, "Snare", 38, 0);
  Pin[4].set(A4, "Snare", 38, 0, true);
  Pin[5].set(A5, "Crash", 49, 0);
  Pin[6].set(A6, "None", 4, 0, true);
  Pin[7].set(A7, "Hihat", 42, 0);
  Pin[8].set(A8, "None", 4, 0, true);
  Pin[9].set(A9, "Kick", 36, 0);
  Pin[10].set(A10, "Ride", 51, 0);
  Pin[11].set(A11, "Tom", 45, 0);
  Pin[12].set(A12, "Floor", 41, 0);

  Dpin[0].set(22, "Choke", 83, 0);
  Dpin[1].set(23, "None", 87, 0, true);
}

void realDrum(){
  Pin[0].set(A0, "HH Control2", 4, 1);
  Pin[1].set(A1, "None", 4, 0, true);
  Pin[2].set(A2, "None", 4, 0, true);
  Pin[3].set(A3, "Snare", 38, 0);
  Pin[4].set(A4, "Snare", 38, 0, true);
  Pin[5].set(A5, "Crash", 49, 0);
  Pin[6].set(A6, "None", 4, 0, true);
  Pin[7].set(A7, "Hihat", 42, 0);
  Pin[8].set(A8, "None", 4, 0, true);
  Pin[9].set(A9, "Kick", 36, 0);
  Pin[10].set(A10, "Ride", 51, 0);
  Pin[11].set(A11, "Tom", 45, 0);
  Pin[12].set(A12, "Floor", 41, 0);

  Dpin[0].set(22, "Choke", 83, 0);
  Dpin[1].set(23, "None", 87, 0, true);
}

