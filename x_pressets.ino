// Config to acess Pressets
// Add preset:

String getPresset(int num){
  switch(num) {
    case 0:
      return "Default";
      break;
    case 1:
      return "Real Drums APP";
      break;
    // Add presset
    //case up + 1:
    //  return "presset name"
    //  break;
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
    // Add presset
    //case up+1:
    //  presetFunction();
    //  break;
    default:
      return;
  }
}

