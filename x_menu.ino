class menu {
  byte level = 0;
  byte layer = 0;
  byte option = 0;
  byte onScreen = 3;
  byte pin = 0;

  public:
  menu(){}

  void init(){
    handler.replaceValue(0, "Midi Drum V1.0");
    handler.replaceValue(1, "CreatedBy:");
    handler.replaceValue(2, "Julio Maranhao");
    handler.replaceValue(3, "All Rights Reserved.");

    delay(3000);

    mainScr();
  }

  void navigate(){
    switch (level){
      case 0:
        mainScrNav();
        break;
      case 1:
        playModeNav();
        break;
      case 2:
        sensibilityModeNav();
        break;
      case 3:
        switch (layer){
          case 0:
            settingsModeNav();
            break;
          case 1:
            analogPinsNav();
            break;
          case 2:
            digitalPinsNav();
            break;
          case 3:
            globalSettingsNav();
            break;
        }
        break;
      case 4:
        pressetsNav();
        break;
    }
  }

  void mainScr() {
    option = 0;
    handler.replaceValue(0, "Play Mode");
    handler.replaceValue(1, "Sensibility");
    handler.replaceValue(2, "Settings");
    handler.replaceValue(3, "Pressets");

    handler.indicatePosition(option);
  }

  void mainScrNav(){
    if(Buttons[1].isPressed()) {
      if(option > 0) {
        option -= 1;
        handler.indicatePosition(option);
      }
    }
    if(Buttons[2].isPressed()) {
      if(option < 3) {
        option += 1;
        handler.indicatePosition(option);
      }
    }
    if (Buttons[0].isPressed()) {
      level = option + 1;
      if(level == 3) {settingsScr(); return;}
      if(level == 4) {updateScreen = true;}
      option = 0;
    }
  }

  void playModeNav(){
    if(!(readScan)) {handler.replaceValue(3, "");}
    readScan = true;
    handler.replaceValue(0, "Midi Drum V1.0");
    handler.replaceValue(1, "--------------------");
    handler.replaceValue(2, "Name|Note|Velocity");

    handler.stopBlink();
    if(Buttons[0].hold() >= 1) {
      level = 0;
      readScan = false;
      mainScr();
    }
  }

  void sensibilityModeNav(){
    if(!(readScan)) {
      handler.replaceValue(3, "");
      option = 0;
      handler.replaceValue(0, addBlankBetweenValues("Name:", String(Pin[pin].name)));
      handler.replaceValue(1, addBlankBetweenValues("Min:", String(Pin[pin].minSens)));
      handler.replaceValue(2, addBlankBetweenValues("Max:", String(Pin[pin].maxSens)));
      handler.indicatePosition(option);
    }
    if(updateScreen) {
      handler.replaceSettingsValue(0, addBlankBetweenValues("Name:", String(Pin[pin].name)));
      handler.replaceSettingsValue(1, addBlankBetweenValues("Min:", String(Pin[pin].minSens)));
      handler.replaceSettingsValue(2, addBlankBetweenValues("Max:", String(Pin[pin].maxSens)));
      handler.resetIndication(option);
      updateScreen = false;
    }
    readScan = true;

    if(Buttons[0].hold() >= 1) {
      level = 0;
      pin = 0;
      option = 0;
      readScan = false;
      mainScr();
    }
    if (Buttons[1].isPressed()){
      if(option == 0){ return;}
      option -= 1;
      handler.indicatePosition(option);
    }
    if (Buttons[2].isPressed()){
      if(option + 1 > 2){ return;}
      option += 1;
      handler.indicatePosition(option);
    }
    if(Buttons[3].hold() >= 1){
      switch(option){
        case 0:
          pin += 1;
          break;
        case 1:
          Pin[pin].minSens += 50;
          break;
        case 2:
          Pin[pin].maxSens += 50;
          break;
      }
      updateScreen = true;
    }
    if(Buttons[4].hold() >= 1){
      switch(option){
        case 0:
          pin -= 1;
          break;
        case 1:
          Pin[pin].minSens -= 50;
          break;
        case 2:
          Pin[pin].maxSens -= 50;
          break;
      }
      updateScreen = true;
    }
    if(Buttons[3].isPressed()){
      switch(option){
        case 0:
          pin += 1;
          break;
        case 1:
          Pin[pin].minSens += 1;
          break;
        case 2:
          Pin[pin].maxSens += 1;
          break;
      }
      updateScreen = true;
    }
    if(Buttons[4].isPressed()){
      switch(option){
        case 0:
          pin -= 1;
          break;
        case 1:
          Pin[pin].minSens -= 1;
          break;
        case 2:
          Pin[pin].maxSens -= 1;
          break;
      }
      updateScreen = true;
    }
    
    // Guard For Max|Min value
    if (pin == nPin) {pin = 0;}
    if (pin >= nPin-1) {pin = nPin-1;}
    if (Pin[pin].minSens > 1024){Pin[pin].minSens = 1024;}
    if (Pin[pin].maxSens > 1024){Pin[pin].maxSens = 1024;}
    if (Pin[pin].minSens < 0){Pin[pin].minSens = 0;}
    if (Pin[pin].maxSens < 0){Pin[pin].maxSens = 0;}
  }

  void settingsScr(){
    option = 1;
    handler.replaceValue(0, "Settings:");
    handler.replaceValue(1, "Analog Pins");
    handler.replaceValue(2, "Digital Pins");
    handler.replaceValue(3, "Global Settings");

    handler.indicatePosition(option);
  }

  void settingsModeNav(){
    if(Buttons[0].hold() >= 1) {
      level = 0;
      layer = 0;
      readScan = false;
      mainScr();
    }
    if(Buttons[0].isPressed()) {
      layer = option;
      option = 0;
      updateScreen = true;
    }
    if (Buttons[1].isPressed()){
      if(option == 1){ return;}
      option -= 1;
      handler.indicatePosition(option);
    }
    if (Buttons[2].isPressed()){
      if(option == 3){ return;}
      option += 1;
      handler.indicatePosition(option);
    }
  }

  void analogPinsNav(){
    if(updateScreen){
      handler.replaceSettingsValue(0, getAnalogPinProperty(onScreen - 3));
      handler.replaceSettingsValue(1, getAnalogPinProperty(onScreen - 2));
      handler.replaceSettingsValue(2, getAnalogPinProperty(onScreen - 1));
      handler.replaceSettingsValue(3, getAnalogPinProperty(onScreen));
      handler.indicatePosition(option - (onScreen -3));
      updateScreen = false;
    }

    if(Buttons[0].hold() >= 1) {
      level = 3;
      layer = 0;
      readScan = false;
      updateScreen = false;
      settingsScr();
    }
    if (Buttons[1].isPressed()){
      if(option == 0){ return;}
      option -= 1;
      if (option + 3 < onScreen) {
        onScreen -= 1;
      }
      handler.indicatePosition(option);
      updateScreen = true;
    }
    if (Buttons[2].isPressed()){
      if(option == 6){ return;}
      option += 1;
      if (option > onScreen) {
        onScreen += 1;
      }
      handler.indicatePosition(option);
      updateScreen = true;
    }
    if (Buttons[3].isPressed()){
      setAnalogPinProperty(option, false);
      updateScreen = true;
    }
    if (Buttons[4].isPressed()){
      setAnalogPinProperty(option, true);
      updateScreen = true;
    }
    // Guard For Max|Min value
    if (pin == nPin) {pin = 0;}
    if (pin >= nPin-1) {pin = nPin-1;}
  }

  void digitalPinsNav(){
    if(updateScreen){
      handler.replaceSettingsValue(0, getDigitalPinProperty(onScreen - 3));
      handler.replaceSettingsValue(1, getDigitalPinProperty(onScreen - 2));
      handler.replaceSettingsValue(2, getDigitalPinProperty(onScreen - 1));
      handler.replaceSettingsValue(3, getDigitalPinProperty(onScreen));
      handler.indicatePosition(option - (onScreen -3));
      updateScreen = false;
    }

    if(Buttons[0].hold() >= 1) {
      level = 3;
      layer = 0;
      readScan = false;
      updateScreen = false;
      settingsScr();
    }
    if (Buttons[1].isPressed()){
      if(option == 0){ return;}
      option -= 1;
      if (option + 3 < onScreen) {
        onScreen -= 1;
      }
      handler.indicatePosition(option);
      updateScreen = true;
    }
    if (Buttons[2].isPressed()){
      if(option == 5){ return;}
      option += 1;
      if (option > onScreen) {
        onScreen += 1;
      }
      handler.indicatePosition(option);
      updateScreen = true;
    }
    if (Buttons[3].isPressed()){
      setDigitalPinProperty(option, false);
      updateScreen = true;
    }
    if (Buttons[4].isPressed()){
      setDigitalPinProperty(option, true);
      updateScreen = true;
    }
    // Guard For Max|Min value
    if (pin == nDpin) {pin = 0;}
    if (pin >= nDpin-1) {pin = nDpin-1;}
  }

  void globalSettingsNav(){
    if(updateScreen){
      handler.replaceSettingsValue(0, getGlobalProperty(onScreen - 3));
      handler.replaceSettingsValue(1, getGlobalProperty(onScreen - 2));
      handler.replaceSettingsValue(2, getGlobalProperty(onScreen - 1));
      handler.replaceSettingsValue(3, getGlobalProperty(onScreen));
      handler.indicatePosition(option - (onScreen -3));
      updateScreen = false;
    }
    if(Buttons[0].hold() >= 1) {
      level = 3;
      layer = 0;
      readScan = false;
      updateScreen = false;
      settingsScr();
    }
    if (Buttons[1].isPressed()){
      if(option == 0){ return;}
      option -= 1;
      if (option + 3 < onScreen) {
        onScreen -= 1;
      }
      handler.indicatePosition(option);
      updateScreen = true;
    }
    if (Buttons[2].isPressed()){
      if(option == 3){ return;}
      option += 1;
      if (option > onScreen) {
        onScreen += 1;
      }
      handler.indicatePosition(option);
      updateScreen = true;
    }
    if (Buttons[3].isPressed()){
      setGlobalProperty(option, false);
      updateScreen = true;
    }
    if (Buttons[4].isPressed()){
      setGlobalProperty(option, true);
      updateScreen = true;
    }
  }

  void pressetsNav(){
    if(updateScreen){
      handler.replaceValue(0, getPresset(onScreen - 3));
      handler.replaceValue(1, getPresset(onScreen - 2));
      handler.replaceValue(2, getPresset(onScreen - 1));
      handler.replaceValue(3, getPresset(onScreen));
      handler.indicatePosition(option - (onScreen -3));
      updateScreen = false;
    }
    if(Buttons[0].hold() >= 1) {
      level = 0;
      layer = 0;
      readScan = false;
      updateScreen = false;
      mainScr();
    }
    if(Buttons[0].isPressed()) {
      setPresset(option);
      level = 0;
      layer = 0;
      readScan = false;
      updateScreen = false;
      mainScr();
    }
    if (Buttons[1].isPressed()){
      if(option == 0){ return;}
      option -= 1;
      if (option + 3 < onScreen) {
        onScreen -= 1;
      }
      handler.indicatePosition(option);
      updateScreen = true;
    }
    if (Buttons[2].isPressed()){
      if(option == PRESSETS - 1){ return;}
      option += 1;
      if (option > onScreen) {
        onScreen += 1;
      }
      handler.indicatePosition(option);
      updateScreen = true;
    }
  }

  private:
  String addBlankBetweenValues(String a, String b){
    byte gap = 10 - a.length();
    String gapText = "";
    if (gap > 0) {
      for (int i = 1; i < gap; i++){
        gapText = gapText + " ";
      }
      return a + gapText + b;
    }
    return a + b;
  }

  String getAnalogPinProperty(byte num) {
    switch(num){
      case 0:
        return addBlankBetweenValues("Name:", String(Pin[pin].name));
        break;
      case 1:
        return addBlankBetweenValues("Note:", String(Pin[pin].note));
        break;
      case 2:
        return addBlankBetweenValues("Type:", String(Pin[pin].getType()));
        break;
      case 3:
        return addBlankBetweenValues("Curve:", Pin[pin].getCurve());
        break;
      case 4:
        return addBlankBetweenValues("MaskTime:", String(Pin[pin].maskTime));
        break;
      case 5:
        return addBlankBetweenValues("Gain:", String(Pin[pin].gain));
        break;
      case 6:
        return addBlankBetweenValues("Disabled:", Pin[pin].getDisabled());
        break;
    }
  }

  void setAnalogPinProperty(byte num, bool reverse) {
    switch(num){
      case 0:
        if(reverse){pin -= 1;} else {pin += 1;} 
        break;
      case 1:
        if(reverse){Pin[pin].note -= 1;} else{Pin[pin].note += 1;}
        break;
      case 2:
        Pin[pin].changeType(reverse);
        break;
      case 3:
        Pin[pin].changeCurve(reverse);
        break;
      case 4:
        if(reverse){Pin[pin].maskTime -= 1;} else{Pin[pin].maskTime += 1;}
        break;
      case 5:
        if(reverse){Pin[pin].gain -= 1;} else{Pin[pin].gain += 1;}
        break;
      case 6:
        Pin[pin].changeDisabled();
        break;
    }
  }

  String getDigitalPinProperty(byte num) {
    switch(num){
      case 0:
        return addBlankBetweenValues("Name:", String(Dpin[pin].name));
        break;
      case 1:
        return addBlankBetweenValues("Note:", String(Dpin[pin].note));
        break;
      case 2:
        return addBlankBetweenValues("Type:", String(Dpin[pin].getType()));
        break;
      case 3:
        return addBlankBetweenValues("MaskTime:", String(Dpin[pin].maskTime));
        break;
      case 4:
        return addBlankBetweenValues("DefState:", Dpin[pin].getDefState());
        break;
      case 5:
        return addBlankBetweenValues("Disabled:", Dpin[pin].getDisabled());
        break;
    }
  }

  void setDigitalPinProperty(byte num, bool reverse) {
    switch(num){
      case 0:
        if(reverse){pin -= 1;} else {pin += 1;};
        break;
      case 1:
        if(reverse){Dpin[pin].note -= 1;} else{Dpin[pin].note += 1;}
        break;
      case 2:
        Dpin[pin].changeType(reverse);
        break;
      case 3:
        if(reverse){Dpin[pin].maskTime -= 1;} else{Dpin[pin].maskTime += 1;}
        break;
      case 4:
        Dpin[pin].changeDefState();
        break;
      case 5:
        Dpin[pin].changeDisabled();
        break;
    }
  }

  String getGlobalProperty(byte num) {
    switch(num){
      case 0:
        return addBlankBetweenValues("Channel:", String(midiChannel));
        break;
      case 1:
        return addBlankBetweenValues("HHSens:", String(hhControlSens));
        break;
      case 2:
        if(hhControlMode){
          return addBlankBetweenValues("HHMode:", "CC");
        } else {
          return addBlankBetweenValues("HHMode:", "Mecha");
        }
        break;
      case 3:
        if(hhControlType){
          return addBlankBetweenValues("HHType:", "Analog");
        } else {
          return addBlankBetweenValues("HHType:", "Digital");
        }
        break;
    }
  }

  void setGlobalProperty(byte num, bool reverse) {
    switch(num){
      case 0:
        if(reverse){
          midiChannel -= 1;
        } else {
          midiChannel += 1;
        }
        if (midiChannel == 16){ midiChannel = 0;}
        if (midiChannel > 16){ midiChannel = 15;}
        break;
      case 1:
        if(reverse){
          hhControlSens -= 1;
        } else {
          hhControlSens += 1;
        }
        break;
      case 2:
        if(hhControlMode){
          hhControlMode = false;
        } else {
          hhControlMode = true;
        }
        break;
      case 3:
        if(hhControlType){
          hhControlType = false;
        } else {
          hhControlType = true;
        }
        break;
    }
  }

}mainMenu;
