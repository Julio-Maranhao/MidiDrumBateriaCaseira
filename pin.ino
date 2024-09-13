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
  int maxReading;
  int yn_1;
  public:
  char* name;
  byte input;
  byte muxChannel;
  char curve;
  byte type;
  byte note;
  byte scanTime;
  byte maskTime;
  byte retrigger;
  byte curveForm;
  byte gain;
  byte thresold;  // Parameter for value change
  bool isMultiplex;
  bool disabled;
  byte state;

  public:
  pin(){
    gain = 20;
    curveForm = 110;
    curve = Linear;
    scanTime = 10;
    maskTime = 30;
    retrigger = 30;
    thresold = 20;
    time = 0;
    maxReading = 0;
    state = Normal_Time;
    yn_1 = 0;
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
    byte vel;
    long globalTime;
    int yn_0;
    switch (type) {
      case 1:
        ///////////////////////
        /////// OPTICAL ///////
        ///////////////////////
        if (isMultiplex){multiplex.setChannel(muxChannel);}
        vel = analogRead(input)/8;
        if (vel > (maxReading + thresold) || vel < (maxReading - thresold)) {
          globalTime = millis();
          if (globalTime - time > maskTime) {
            fastCCOn(midiChannel, note, vel);
            maxReading = vel;
            if(readScan){
              handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(vel));
            }
            time = globalTime;
          }
        }
        break;
      default:
        ///////////////////////
        //////// PIEZO ////////
        ///////////////////////
        if (isMultiplex){multiplex.setChannel(muxChannel);}
        globalTime = millis();

        // MASK TIME //
        if (state == Mask_Time) {
          if (globalTime - time > maskTime) {
            state = Retrigger_Time;
            time = globalTime;
          }
        }
        yn_0 = 0.5 + ((float)analogRead(input)) * ((float)gain) / 64.0;

        // SCAN TIME //
        if (state == Scan_Time) {
          if (globalTime - time < scanTime) {
            if (yn_0 > maxReading) {maxReading = yn_0;}
          } else {
            state = Piezo_Time;
          }
        }
        // PIEZO TIME //
        if (state == Piezo_Time) {
          vel = calcVelocity();
          fastNoteOn(midiChannel, note, vel);
          state = Mask_Time;
          if(readScan){
            handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(vel));
          }
        }

        // RETRIGGER TIME //
        if (state == Retrigger_Time) {
          int maxRetriggerSensor = maxReading - (globalTime - time) * (retrigger+1)/16;
          if (maxRetriggerSensor > 0) {
            if((yn_0 - yn_1)> thresold && yn_0 > maxRetriggerSensor) {
              state = Scan_Time;
              time = globalTime;
              maxReading = 0;
            }
          } else {
            state = Normal_Time;
          }
        // NORMAL TIME //
        } else if (state == Normal_Time){
          if ((yn_0 - yn_1) > thresold) {
            state = Scan_Time;
            time = globalTime;
            maxReading = 0;
          }
        } 

        yn_1 = yn_0;
    }
  }

  byte playHHMechanicalControl(){
    float read;
    long globalTime;
    int vel;
    byte response;
    if (isMultiplex){multiplex.setChannel(muxChannel);}
    vel = analogRead(input)/8;
    // Change note
    if(vel == 0) {response = 1;}
    response = ceil(vel*hhControlStages/127) + 1;
    // Footsplash
    if (vel > (maxReading + thresold) || vel < (maxReading - thresold)) {
      globalTime = millis();
      if (globalTime - time > maskTime) {
        if(vel >= 100 && (vel - maxReading) >= 70){
          fastNoteOn(midiChannel, note, 127);
          if(readScan){
            handler.replaceValueForce(3, String(name) + "|" + String(note) + "|" + String(127));
          }
        }
        maxReading = vel;
        time = globalTime;
      }
    }
    return response;
  }

  byte calcVelocity() {
    int vel;
    float f = curveForm/32.0;
    if (curve == Linear) {
      vel = 0.5 + (((float)maxReading) * f / 8.0);
    } else {
      int i = maxReading / 128;
      int m = maxReading % 128;
      switch (curve){
        case Exp:
          vel = 0.5 + (((float)m*(_Exp[i+1]-_Exp[i])/128.0) + _Exp[i])*f; 
          break;
        case Log:
          vel = 0.5 + (((float)m*(_Log[i+1]-_Log[i])/128.0) + _Log[i])*f; 
          break;
        case Sigma:
          vel = 0.5 + (((float)m*(_Sigma[i+1]-_Sigma[i])/128.0) + _Sigma[i])*f; 
          break;
        case Flat:
          vel = 0.5 + (((float)m*(_Flat[i+1]-_Flat[i])/128.0) + _Flat[i])*f; 
          break;
      }
    }
    if(vel<=0) return 0;
    if(vel>=127) return 127;
    return vel;
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
      if(curve+1 > 69){return;}
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