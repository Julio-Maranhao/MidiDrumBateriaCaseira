//Carrega a biblioteca do LCD
#include "lcdHandler.h"
#include <LiquidCrystal.h>
#include <math.h>
///// CONFIGURAÇÃO /////
#define USEMIDI 1             // 0 = 115200 SerialSpeed; 1 = 31250 SerialSpeed MIDI
#define USEMULTIPLEX 1        // 1 = Usou multiplex para extender entradas; 0 = Não usou
#define ANALOGPINS 12         // Define a quantidade total de pinos analogicos conectados no Arduino/Multiplexador
#define ANALOGINPUTS 12       // Define a quantidade total de pinos analogicos do Arduino
#define DIGITALPINS 3         // Define a quantidade total de pinos digitais usados no projeto
////////////////////////

// Function to play MIDI
#define fastNoteOn(_note,_velocity) { Serial.write(0x90 | 9);Serial.write(_note);Serial.write(_velocity); }
#define fastCCOn(_note,_velocity) { Serial.write(0xB0 | 9);Serial.write(_note);Serial.write(_velocity); }

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
//Determina a quantidade de pinos
const byte nPin = ANALOGPINS;

//Inicializa o LCD
LcdHandler handler = LcdHandler();

//Numeração dos pinos
byte buttons[] = {CIMA, BAIXO, ESQUERDA, DIREITA, OK};

//Listas de dados de Pinos Analógicos do Arduino
byte inputList[ANALOGINPUTS];
String inputNames[ANALOGINPUTS];
char* curveNames[3] = {"A", "B", "C"};
char* analogTypes[3] = {"Piezo", "Optical", "Pot"};


