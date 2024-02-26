//Carrega a biblioteca do LCD
#include "lcdHandler.h"
#include <LiquidCrystal.h>
#include <math.h>
///// CONFIGURAÇÃO /////
#define USEMIDI 0             // 0 = 115200 SerialSpeed; 1 = 31250 SerialSpeed MIDI
#define ANALOGPINS 16            // Define a quantidade total de pinos analogicos
////////////////////////

// Function to play MIDI
//#define fastNoteOn(_note,_velocity) { Serial.write(0x90 | 0x09);Serial.write(_note);Serial.write(_velocity); }
//#define fastMidiCC(_number,_value) { Serial.write((0xB0 | 0x09)); Serial.write(_number); Serial.write(_value); }

// Defines Aux
#define TIMEFUNCTION millis()

// Defines Multiplex Out Pins
#define MX1 30
#define MX2 31
#define MX3 32
#define MX4 33
// Defines Control Buttons Pins
# define CIMA 24
# define BAIXO 25
# define DIREITA 26
# define ESQUERDA 27
# define OK 28

# define ANALOG12 A12

//Inicializa o LCD
LcdHandler handler = LcdHandler();
//Determina a quantidade de pinos
const byte nPin = ANALOGPINS;
//Numeração dos pinos
int buttons[] = {CIMA, BAIXO, ESQUERDA, DIREITA, OK};
struct lcdMessage {
  bool trigger = false;
  String pinName;
  String pinNote;
  String pinVelocity;
};

