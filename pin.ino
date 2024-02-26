// analog Read 0 - 1023 (1024 numbers) float

class pin {
  int input;
  int muxChannel;
  int note;
  //int scanTime;
  int maskTime;
  int time;
  int currentTime;
  int gain;
  int type;
  String name;
  String curve;
  float minSens;
  float maxSens;
  bool disabled;
  bool isMultiplex;

  public:
  pin(){
    //scanTime = 10;
    maskTime = 50;
    gain = 0;
    curve = "Linear";
    minSens = 400.00;
    maxSens = 1024.00;
    currentTime = 0;
    time = 0;
  }

  void set(int pinInput, String pinName, int pinNote, int pinType, bool isDisabled = false){
    input = pinInput;
    note = pinNote;
    name = pinName;
    type = pinType;
    disabled = isDisabled;
  }

  void Scan(){
    float read = analogRead(input);
    lcdMessage message;
    if (read > minSens) {
      int velocity = round((read - minSens)/(maxSens - minSens) * 127) ;
      Serial.write(0x90 | 0x09);
      Serial.write(note);
      Serial.write(velocity);

      handler.replaceValue(1, name);
      handler.replaceValue(2, String(note));
      handler.replaceValue(3, String(velocity));
    }
  }

  void playMIDI(){
    if (disabled){return;}
    switch (type) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      default:
        ///////////////////////
        //////// PIEZO ////////
        ///////////////////////
        float read = analogRead(input);
        if (read > minSens) {
          long globalTime = TIMEFUNCTION;
          if (globalTime - time > maskTime) {
            int velocity = round((read - minSens)/(maxSens - minSens) * 127) + gain;
              if (velocity > 127){velocity = 127;}

          }
          time = globalTime;
        }
    }
  }

  void setNome(String newName){
    name = newName;
  }

}Pin[nPin] ;