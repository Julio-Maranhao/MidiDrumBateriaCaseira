class dpin {
  byte muxChannel;
  byte type;
  byte lastVelocity;
  long time;
  public:
  byte input;
  char* name;
  byte note;
  byte maskTime;
  bool defaultState;
  bool isMultiplex;
  bool disabled;

  public:
  dpin(){
    time = 0;
    maskTime = 50;
    lastVelocity = 0;
    defaultState = true;
  }

  set (byte pinInput, char* pinName, byte pinNote, byte pinType, bool isDisabled = false){
    input = pinInput;
    note = pinNote;
    name = pinName;
    type = pinType;
    disabled = isDisabled;

    pinMode(input, INPUT_PULLUP);
  }

  void playMIDI(){
    if (disabled){return;}
    bool read;
    long globalTime;
    int velocity;
    switch (type) {
      case 1:
        ///////////////////////
        /////// CONTROL ///////
        ///////////////////////
        if (isMultiplex){multiplex.setChannel(muxChannel);}
        read = digitalRead(input);
        if (read != defaultState) {
          velocity = 127;
          if(lastVelocity != 127){
            fastCCOn(midiChannel, note, velocity);
            lastVelocity = velocity;
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(velocity));
            }
          }
        } else {
          velocity = 0;
          if(lastVelocity != 0){
            fastCCOn(midiChannel, note, velocity);
            lastVelocity = velocity;
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(velocity));
            }
          }
        }
        
        break;
      default:
        ///////////////////////
        ///////// NOTE ////////
        ///////////////////////
        if (isMultiplex){multiplex.setChannel(muxChannel);}
        read = digitalRead(input);
        if (read != defaultState) {
          globalTime = millis();
          if (globalTime - time > maskTime) {
            velocity = 127;
            fastNoteOn(midiChannel, note, velocity);
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(velocity));
            }
          }
          time = globalTime;
        }
    }
  }

  int getMuxChannel(){
    return muxChannel;
  }

  void setMuxChannel(int channel){
    if(channel > 16) {muxChannel = 16; return;}
    if(channel < 0) {muxChannel = 0; return;}
    muxChannel = channel;
  }

  char* getType() {
    return digitalTypes[type];
  }

  void changeType(bool reverse=false) {
    if(reverse){
      if(type == 0){return;}
      type -= 1;
    }else{
      if(type == 1){return;}
      type += 1;
    }
  }

  String getDisabled() {
    if(disabled) {
      return "true";
    } else{
      return "false";
    }
  }

  void changeDisabled(){
  if(disabled){disabled = false;} else {disabled=true;}
  }

  String getDefState() {
    if(defaultState) {
      return "true";
    } else{
      return "false";
    }
  }

  void changeDefState(){
  if(defaultState){defaultState = false;} else {defaultState=true;}
  }

  void changeIsMultiplex(){
  if(isMultiplex){isMultiplex = false;} else {isMultiplex=true;}
  }

} Dpin[nDpin];

