// analog Read 0 - 1023 (1024 numbers) float

class pin {
  int input;
  int muxChannel;
  String name;
  String curve;
  float minSens;
  float maxSens;
  int type;
  int time;
  int currentTime;
  bool isMultiplex;
  bool disabled;
  public:
  int note;
  int scanTime;
  int maskTime;
  int gain;

  public:
  pin(){
    scanTime = 10;
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

  void increaseInput(){
    for (int i = 0; i < sizeof(inputList); i++) {
      if (input == inputList[i]) {
        if (i + 1 > sizeof(inputList) - 1) {return;}
        input = inputList[i + 1];
        return;
      }
    }
  }

  void decreaseInput(){
    for (int i = 0; i < sizeof(inputList); i++) {
      if (input == inputList[i]) {
        if (i - 1 < 0) { return;}
        input = inputList[i - 1];
        return;
      }
    }
  }

  void increaseMuxChannel(){
    for (int i = 0; i < 16; i++) {
      if (input == inputList[i]) {
        if (i + 1 > 15) { return;}
        input = inputList[i + 1];
        return;
      }
    }
  }

  void decreaseMuxChannel(){
    for (int i = 0; i < 16; i++) {
      if (input == inputList[i]) {
        if (i - 1 < 0) { return;}
        input = inputList[i - 1];
        return;
      }
    }
  }

}Pin[nPin];