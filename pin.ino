// analog Read 0 - 1023 (1024 numbers) float

class pin {
  byte input;
  byte muxChannel;
  char curve;
  byte type;
  long time;
  byte lastVelocity;
  public:
  char* name;
  byte note;
  byte maskTime;
  float minSens;
  float maxSens;
  byte gain;
  bool isMultiplex;
  bool disabled;

  public:
  pin(){
    maskTime = 50;
    gain = 0;
    curve = 67;
    minSens = 400.00;
    maxSens = 1024.00;
    time = 0;
    lastVelocity = 0;
  }

  void set(byte pinInput, char* pinName, byte pinNote, byte pinType, bool isDisabled = false){
    input = pinInput;
    note = pinNote;
    name = pinName;
    type = pinType;
    disabled = isDisabled;
  }

  void playMIDI(){
    if (disabled){return;}
    float read;
    long globalTime;
    int velocity;
    switch (type) {
      case 1:
        ///////////////////////
        /////// OPTICAL ///////
        ///////////////////////
        if (isMultiplex){multiplex.setChannel(muxChannel);}
        read = analogRead(input);
        if (read > minSens) {
          globalTime = millis();
          if (globalTime - time > maskTime) {
            velocity = round((read - minSens)/(maxSens - minSens) * 127) + gain;
            if (curve != 67) {
              if (curve == 65) {
                velocity = ceil(-0.0085*pow(velocity,2) + 2.078*velocity);
              } else {
                velocity = ceil(0.0068*pow(velocity,2) + 0.1325*velocity);
              }
            }
            if (velocity > 127){velocity = 127;}
            if(abs(velocity - lastVelocity) > HHCSENS){
              fastCCOn(note, velocity);
              lastVelocity = velocity;
              if(readScan){
                handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(velocity));
              }
              time = globalTime;
            }
          }
        }
        break;
      default:
        ///////////////////////
        //////// PIEZO ////////
        ///////////////////////
        if (isMultiplex){multiplex.setChannel(muxChannel);}
        read = analogRead(input);
        if (read > minSens) {
          globalTime = millis();
          if (globalTime - time > maskTime) {
            velocity = round((read - minSens)/(maxSens - minSens) * 127) + gain;
            if (curve != 67) {
              if (curve == 65) {
                velocity = ceil(-0.0085*pow(velocity,2) + 2.078*velocity);
              } else {
                velocity = ceil(0.0068*pow(velocity,2) + 0.1325*velocity);
              }
            }
            if (velocity > 127){velocity = 127;}
            fastNoteOn(note, velocity);
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(velocity));
            }
          }
          time = globalTime;
        }
    }
  }

  int getInput(){
    return input - A0;    
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

  String getCurve() {
    String cName = " ";
    cName.setCharAt(0, curve);
    return cName;
  }

  void changeCurve(bool reverse=false) {
    if(reverse){
      if(curve == 65){return;}
      curve -= 1;
    }else{
      if(curve+1 > 67){return;}
      curve += 1;
    }
  }

  char* getType() {
    return analogTypes[type];
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

}Pin[nPin];