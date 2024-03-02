class dpin {
  byte input;
  byte muxChannel;
  byte type;
  long time;
  public:
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
  }

  set (byte pinInput, char* pinName, byte pinNote, byte pinType, bool isDisabled = false){
    input = pinInput;
    note = pinNote;
    name = pinName;
    type = pinType;
    disabled = isDisabled;
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

  void changeIsMultiplex(){
  if(isMultiplex){isMultiplex = false;} else {isMultiplex=true;}
  }

} Dpin[nDpin];

