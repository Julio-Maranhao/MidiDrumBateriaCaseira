//Carrega a biblioteca do LCD
#include "lcdHandler.h"
#include <math.h>
#include <EEPROM.h>

///// CONFIGURAÇÃO /////
#define USEMIDI 1             // 0 = 115200 SerialSpeed; 1 = 31250 SerialSpeed MIDI
#define USEMULTIPLEX 1        // 1 = Usou multiplex para extender entradas; 0 = Não usou
#define ANALOGPINS 13         // Define a quantidade total de pinos analogicos conectados no Arduino/Multiplexador
#define DIGITALPINS 2         // Define a quantidade total de pinos digitais usados no projeto
#define MIDICHANNEL 0         // Define o indice do Channel do MIDI -> (VALOR + 1) -> Se 0 -> MIDI Channel = 1
////////////////////////

// Function to play MIDI
#define fastNoteOn(_note,_velocity) { Serial.write(0x90 | MIDICHANNEL);Serial.write(_note);Serial.write(_velocity); }
#define fastCCOn(_note,_velocity) { Serial.write(0xB0 | MIDICHANNEL);Serial.write(_note);Serial.write(_velocity); }

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

//Determina a quantidade de pinos
const byte nPin = ANALOGPINS;
const byte nDpin = DIGITALPINS;

//Inicializa o LCD
LcdHandler handler = LcdHandler();

//Dados menu
bool readScan = false;
bool updateScreen = false;

//Listas de dados de Pinos Analógicos do Arduino
char* analogTypes[2] = {"Piezo", "Optical"};
char* digitalTypes[2] = {"Note", "Control"};


