// analog Read 0 - 1023 (1024 numbers) float

class pin {
  byte input;
  byte muxChannel;
  char curve;
  float minSens;
  float maxSens;
  byte type;
  long time;
  int currentTime;
  public:
  char* name;
  byte note;
  byte scanTime;
  byte maskTime;
  byte gain;
  bool isMultiplex;
  bool disabled;

  public:
  pin(){
    scanTime = 10;
    maskTime = 50;
    gain = 0;
    curve = "C";
    minSens = 400.00;
    maxSens = 1024.00;
    currentTime = 0;
    time = 0;
  }

  void set(byte pinInput, char* pinName, byte pinNote, byte pinType, bool isDisabled = false){
    input = pinInput;
    note = pinNote;
    name = pinName;
    type = pinType;
    disabled = isDisabled;
  }

  void scan(){
    if (disabled){return;}
    if (isMultiplex){multiplex.setChannel(muxChannel);}
    float read = analogRead(input);
    if (read > minSens) {
      int velocity = round((read - minSens)/(maxSens - minSens) * 127) ;
      fastNoteOn(note, velocity);

      handler.replaceValue(1, name);
      handler.replaceValue(2, String(note));
      handler.replaceValue(3, String(velocity));
    }
  }

  void playMIDI(){
    if (disabled){return;}
    switch (type) {
      case 1:
        ///////////////////////
        //// POTENTIOMETER ////
        ///////////////////////
        break;
      case 2:
        ///////////////////////
        /////// OPTICAL ///////
        ///////////////////////
        break;
      default:
        ///////////////////////
        //////// PIEZO ////////
        ///////////////////////
        if (isMultiplex){multiplex.setChannel(muxChannel);}
        float read = analogRead(input);
        if (read > minSens) {
          long globalTime = TIMEFUNCTION;
          if (globalTime - time > maskTime) {
            int velocity = round((read - minSens)/(maxSens - minSens) * 127) + gain;
              if (velocity > 127){velocity = 127;}
            fastNoteOn(note, velocity);
          }
          time = globalTime;
        }
    }
  }
  // SERÀ COM GET E SET OU PROTECTED E SET

  int getInput(){
    return input - A0;    
  }

  String getInputName(){
    return inputNames[input - A0];
  }

  void setInput(int pinNumber) {
    if(pinNumber > ANALOGPINS) {
      input = ANALOGPINS + A0;
      return;
      }
    if(pinNumber < 0){
      input = A0;
      return;
    }
    input = A0 + pinNumber;
  }

  int getMuxChannel(){
    return muxChannel;
  }

  void setMuxChannel(int channel){
    if(channel > 16) {muxChannel = 16; return;}
    if(channel < 0) {muxChannel = 0; return;}
    muxChannel = channel;
  }

  char getCurve() {
    return curve;
  }

  void setCurve(char curveName) {
    curve = curveName;
  }

  char* getType() {
    return analogTypes[type];
  }

  void changeType(bool reverse=false) {
    if(reverse){
      if(type-1 > 0){return;}
      type -= 1;
    }else{
      if(type+1 > sizeof(analogTypes)){return;}
      type += 1;
    }
  }

 void changeDisabled(){
  if(disabled){disabled = false;} else {disabled=true;}
 }

 void changeIsMultiplex(){
  if(isMultiplex){isMultiplex = false;} else {isMultiplex=true;}
 }

}Pin[nPin];