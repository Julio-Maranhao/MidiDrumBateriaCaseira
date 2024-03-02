class controlButton {
  byte pin;
  bool defaultState;
  long time;
  int miliSeconds;
  public:
  bool state;

  public:
  controlButton (){
    state = false;
  }

  void set (byte currentPin, bool defState){
    pin = currentPin;
    defaultState = defState;
  }

  void readButton(){
    long currentTime = millis();
    bool buttonState = digitalRead(pin);
    //Serial.println(buttonState);
    if(!(state)) {
      if(buttonState != defaultState){
        if(miliSeconds > 0){miliSeconds = currentTime - time; return;}
        time = currentTime;
        miliSeconds = 1;
      } else {
        if(miliSeconds > 0){state = true;}
      }
    } else {
      if(buttonState != defaultState){
        state = false;
        time = currentTime;
        miliSeconds = 1;
      }
    }
  }

  bool isPressed (){
    if(state) {
      state = false;
      miliSeconds = 0;
      return true;
    } else {
      return false;
    }
  }

  int hold (){
    if(!(state)) {return 0;}
    int mili = floor(miliSeconds/1000);
    if (mili == 0){return 0;}
    state = false;
    miliSeconds = 0;
    return mili;
  }

  void reset() {
    state = false;
    miliSeconds = 0;
  }

}Buttons[5];