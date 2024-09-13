void saveGlobalConfigs(){
  int add = 0;
  EEPROM.put(add, midiChannel);
  add += sizeof(midiChannel);
  EEPROM.put(add, hhPin);
  add += sizeof(hhPin);
  EEPROM.put(add, hhControlPin);
  add += sizeof(hhControlPin);
  EEPROM.put(add, hhControlMode);
  add += sizeof(hhControlMode);
  EEPROM.put(add, hhControlType);
  add += sizeof(hhControlType);
  EEPROM.put(add, hhControlStages);
  add += sizeof(hhControlStages);
  EEPROM.put(add, hhNote1);
  add += sizeof(hhNote1);
  EEPROM.put(add, hhNote2);
  add += sizeof(hhNote2);
  EEPROM.put(add, hhNote3);
  add += sizeof(hhNote3);

  // For Pins
  for(int i = 0; i<ANALOGPINS; i++){
    EEPROM.put(add, Pin[i].input);
    add += sizeof(Pin[i].input);
    EEPROM.put(add, Pin[i].muxChannel);
    add += sizeof(Pin[i].muxChannel);
    EEPROM.put(add, Pin[i].curve);
    add += sizeof(Pin[i].curve);
    EEPROM.put(add, Pin[i].type);
    add += sizeof(Pin[i].type);
    EEPROM.put(add, Pin[i].name);
    add += sizeof(Pin[i].name);
    EEPROM.put(add, Pin[i].note);
    add += sizeof(Pin[i].note);
    EEPROM.put(add, Pin[i].maskTime);
    add += sizeof(Pin[i].maskTime);
    EEPROM.put(add, Pin[i].gain);
    add += sizeof(Pin[i].gain);
    EEPROM.put(add, Pin[i].isMultiplex);
    add += sizeof(Pin[i].isMultiplex);
    EEPROM.put(add, Pin[i].disabled);
    add += sizeof(Pin[i].disabled);
    EEPROM.put(add, Pin[i].scanTime);
    add += sizeof(Pin[i].scanTime);
    EEPROM.put(add, Pin[i].retrigger);
    add += sizeof(Pin[i].retrigger);
    EEPROM.put(add, Pin[i].curveForm);
    add += sizeof(Pin[i].curveForm);
    EEPROM.put(add, Pin[i].thresold);
    add += sizeof(Pin[i].thresold);
  }

  // For Dpins
  for(int i = 0; i<DIGITALPINS; i++){
    EEPROM.put(add, Dpin[i].input);
    add += sizeof(Dpin[i].input);
    EEPROM.put(add, Dpin[i].muxChannel);
    add += sizeof(Dpin[i].muxChannel);
    EEPROM.put(add, Dpin[i].type);
    add += sizeof(Dpin[i].type);
    EEPROM.put(add, Dpin[i].name);
    add += sizeof(Dpin[i].name);
    EEPROM.put(add, Dpin[i].note);
    add += sizeof(Dpin[i].note);
    EEPROM.put(add, Dpin[i].maskTime);
    add += sizeof(Dpin[i].maskTime);
    EEPROM.put(add, Dpin[i].defaultState);
    add += sizeof(Dpin[i].defaultState);
    EEPROM.put(add, Dpin[i].isMultiplex);
    add += sizeof(Dpin[i].isMultiplex);
    EEPROM.put(add, Dpin[i].disabled);
    add += sizeof(Dpin[i].disabled);
  }
  handler.replaceValue(0, "MIDI MAP");
  handler.replaceValue(1, "Saving");
  handler.replaceValue(2, "Do not turn off!");
  handler.replaceValue(3, "");
  delay(add*2);
  handler.replaceValue(1, "Saving.");
  delay(add*2);
  handler.replaceValue(1, "Saving..");
  delay(add*2);
  handler.replaceValue(1, "Saving...");
  delay(add*2);
  handler.replaceValue(1, "Saving....");
  
  mainMenu.resetMenu();
}

void loadGlobalConfigs(){
  int add = 0;
  EEPROM.get(add, midiChannel);
  add += sizeof(midiChannel);
  EEPROM.get(add, hhPin);
  add += sizeof(hhPin);
  EEPROM.get(add, hhControlPin);
  add += sizeof(hhControlPin);
  EEPROM.get(add, hhControlMode);
  add += sizeof(hhControlMode);
  EEPROM.get(add, hhControlType);
  add += sizeof(hhControlType);
  EEPROM.get(add, hhControlStages);
  add += sizeof(hhControlStages);
  EEPROM.get(add, hhNote1);
  add += sizeof(hhNote1);
  EEPROM.get(add, hhNote2);
  add += sizeof(hhNote2);
  EEPROM.get(add, hhNote3);
  add += sizeof(hhNote3);

  // For Pins
  for(int i = 0; i<ANALOGPINS; i++){
    EEPROM.get(add, Pin[i].input);
    add += sizeof(Pin[i].input);
    EEPROM.get(add, Pin[i].muxChannel);
    add += sizeof(Pin[i].muxChannel);
    EEPROM.get(add, Pin[i].curve);
    add += sizeof(Pin[i].curve);
    EEPROM.get(add, Pin[i].type);
    add += sizeof(Pin[i].type);
    EEPROM.get(add, Pin[i].name);
    add += sizeof(Pin[i].name);
    EEPROM.get(add, Pin[i].note);
    add += sizeof(Pin[i].note);
    EEPROM.get(add, Pin[i].maskTime);
    add += sizeof(Pin[i].maskTime);
    EEPROM.get(add, Pin[i].gain);
    add += sizeof(Pin[i].gain);
    EEPROM.get(add, Pin[i].isMultiplex);
    add += sizeof(Pin[i].isMultiplex);
    EEPROM.get(add, Pin[i].disabled);
    add += sizeof(Pin[i].disabled);
    EEPROM.get(add, Pin[i].scanTime);
    add += sizeof(Pin[i].scanTime);
    EEPROM.get(add, Pin[i].retrigger);
    add += sizeof(Pin[i].retrigger);
    EEPROM.get(add, Pin[i].curveForm);
    add += sizeof(Pin[i].curveForm);
    EEPROM.get(add, Pin[i].thresold);
    add += sizeof(Pin[i].thresold);
  }

  // For Dpins
  for(int i = 0; i<DIGITALPINS; i++){
    EEPROM.get(add, Dpin[i].input);
    add += sizeof(Dpin[i].input);
    EEPROM.get(add, Dpin[i].muxChannel);
    add += sizeof(Dpin[i].muxChannel);
    EEPROM.get(add, Dpin[i].type);
    add += sizeof(Dpin[i].type);
    EEPROM.get(add, Dpin[i].name);
    add += sizeof(Dpin[i].name);
    EEPROM.get(add, Dpin[i].note);
    add += sizeof(Dpin[i].note);
    EEPROM.get(add, Dpin[i].maskTime);
    add += sizeof(Dpin[i].maskTime);
    EEPROM.get(add, Dpin[i].defaultState);
    add += sizeof(Dpin[i].defaultState);
    EEPROM.get(add, Dpin[i].isMultiplex);
    add += sizeof(Dpin[i].isMultiplex);
    EEPROM.get(add, Dpin[i].disabled);
    add += sizeof(Dpin[i].disabled);
  }
  handler.replaceValue(0, "MIDI MAP");
  handler.replaceValue(1, "Loading");
  handler.replaceValue(2, "Do not turn off!");
  handler.replaceValue(3, "");
  delay(add*2);
  handler.replaceValue(1, "Loading.");
  delay(add*2);
  handler.replaceValue(1, "Loading..");
  delay(add*2);
  handler.replaceValue(1, "Loading...");
  delay(add*2);
  handler.replaceValue(1, "Loading....");
  
  mainMenu.resetMenu();
}