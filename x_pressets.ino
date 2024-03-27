// Config to acess Pressets
String getPresset(int num){
  switch(num) {
    case 0:
      return "Default";
      break;
    case 1:
      return "Real Drums APP";
      break;
    case 2:
      return "MT PowerDrums 2";
      break;
    case 3:
      return "Addictive Drums";
      break;
    case 4:
      return "Seven Slate Drums";
      break;
    case 5:
      return "EZ Drummer";
      break;
    case 6:
      return "Toontrack";
      break;
    // Add presset
    //case up + 1:
    //  return "presset name"
    //  break;
    case 7:
      return "Save to Memory";
      break;
    case 8:
      return "Load from Memory";
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
    case 2:
      powerDrum();
      break;
    case 3:
      addictiveDrums();
      break;
    case 4:
      sevenSlate();
      break;
    case 5:
      ezDrummer();
      break;
    case 6:
      toontrack();
      break;
    // Add presset
    //case up+1:
    //  presetFunction();
    //  break;
    case 7:
      saveGlobalConfigs();
      break;
    case 8:
      loadGlobalConfigs();
      break;
    default:
      return;
  }
}

