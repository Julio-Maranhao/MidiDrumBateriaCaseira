//===========CURVE============
const float _Exp[9]={2.33, 3.85, 6.35, 10.48, 17.28, 28.5, 46.99 , 77.47, 127.74}; //e^((x/256)+0,85)
const float _Log[9]={0, 83.67, 98.23, 106.74, 112.78, 117.47, 121.30 , 124.53, 127.34}; //21*ln(0,42*x)
const float _Sigma[9]={2.28, 6.02, 15.13, 34.15, 63.5, 92.84, 111.86 , 120.97, 127.71}; //128/(1+e^((512-x)/128))
const float _Flat[9]={0, 32.86, 46.42, 55.82, 64.0, 72.17, 81.57 , 95.13, 127}; //64-16*ln((1024/x)-1)

//===========CURVE============
enum curve:char
{
  Linear  = 67,
  Exp     = 66,
  Log     = 65,
  Sigma   = 68,
  Flat    = 69
};
//============================

//===========TIME============
enum state:byte
{
  Normal_Time     = 0,
  Scan_Time       = 1,
  Mask_Time       = 2,
  Retrigger_Time  = 3,
  Piezo_Time      = 4
};

// Class to handle Analog Pins
class pin {
  long time;
  byte lastVelocity;
  public:
  byte input;
  byte muxChannel;
  char curve;
  byte type;
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
            if(abs(velocity - lastVelocity) > hhControlSens){
              fastCCOn(midiChannel, note, velocity);
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
            fastNoteOn(midiChannel, note, velocity);
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(velocity));
            }
          }
          time = globalTime;
        }
    }
  }

  byte playHHMechanicalControl(){
    float read;
    long globalTime;
    int velocity;
    byte response;
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
        if(abs(velocity - lastVelocity) > hhControlSens){
          // Footsplash
          byte footVelocity = abs(velocity - lastVelocity);
          if(velocity >= 100 && (velocity - lastVelocity) >= 70){
            fastNoteOn(midiChannel, note, footVelocity-20);
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(footVelocity-20));
            }
          }
          // Change note
          if(velocity == 0) {response = 1;}
          response = ceil(velocity*hhControlStages/127) + 1;
          lastVelocity = velocity;
          
          time = globalTime;
        }
      }
    }
    return response;
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

  void setCurve(char letra) {
    curve = letra;
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