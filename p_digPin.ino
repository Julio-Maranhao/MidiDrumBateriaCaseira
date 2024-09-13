// Class to handle digital Pins
class dpin {
  byte lastVelocity;
  long time;
  public:
  byte input;
  byte muxChannel;
  byte type;
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
    byte vel;
    switch (type) {
      case 1:
        ///////////////////////
        /////// CONTROL ///////
        ///////////////////////
        if (isMultiplex){multiplex.setChannel(muxChannel);}
        read = digitalRead(input);
        if (read != defaultState) {
          vel = 127;
          if(lastVelocity != 127){
            fastCCOn(midiChannel, note, vel);
            lastVelocity = vel;
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(vel));
            }
          }
        } else {
          vel = 0;
          if(lastVelocity != 0){
            fastCCOn(midiChannel, note, vel);
            lastVelocity = vel;
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(vel));
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
            vel = 127;
            //fastNoteOn(midiChannel, note, vel);
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(vel));
            }
          }
          time = globalTime;
        }
    }
  }

  byte playHHMechanicalControl(){
    bool read;
    long globalTime;
    int vel;
    byte response;
    if (isMultiplex){multiplex.setChannel(muxChannel);}
    read = analogRead(input);
    globalTime = millis();
    if (read != defaultState) {
      if (globalTime - time > maskTime) {
        vel = 127;
        response = 2;
      }
      time = globalTime;
      if (lastVelocity == vel) {
        response = 0;
      }
      lastVelocity = vel;
    } else {
      if (globalTime - time > maskTime) {
        vel = 0;
        response = 1;
      }
      time = globalTime;
      if (lastVelocity == vel) {
        response = 0;
      }
      lastVelocity = vel;
    }
    return response;
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

