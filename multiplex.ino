//Class to handle multiplex input

class MuxControl {
  byte controlPin[4] = {MX1, MX2, MX3, MX4};
  /*byte muxChannel[16][4]={
  {0,0,0,0}, //channel 0
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
  {0,0,1,0}, //channel 4
  {1,0,1,0}, //channel 5
  {0,1,1,0}, //channel 6
  {1,1,1,0}, //channel 7
  {0,0,0,1}, //channel 8
  {1,0,0,1}, //channel 9
  {0,1,0,1}, //channel 10
  {1,1,0,1}, //channel 11
  {0,0,1,1}, //channel 12
  {1,0,1,1}, //channel 13
  {0,1,1,1}, //channel 14
  {1,1,1,1}  //channel 15
  };*/

  public:
  MuxControl(){}

  void setMultiplex(){
    // Set pinMode for multiplexer
    pinMode(controlPin[0], OUTPUT); 
    pinMode(controlPin[1], OUTPUT); 
    pinMode(controlPin[2], OUTPUT); 
    pinMode(controlPin[3], OUTPUT); 
  }

  void setChannel(int channel){
    for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], bitRead(channel, i));
    }
  }

} multiplex;


