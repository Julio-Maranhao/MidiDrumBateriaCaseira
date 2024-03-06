//Carrega a biblioteca do LCD
#include "lcdHandler.h"
#include <math.h>
//#include <SD.h>

// Function to play MIDI
#define fastNoteOn(_channel,_note,_velocity) { Serial.write(0x90 | _channel);Serial.write(_note);Serial.write(_velocity); }
#define fastCCOn(_channel,_note,_velocity) { Serial.write(0xB0 | _channel);Serial.write(_note);Serial.write(_velocity); }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// CONFIGURAÇÃO MANUAL /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

///// CONFIGURAÇÃO /////
#define USEMIDI 1             // 0 = 115200 SerialSpeed; 1 = 31250 SerialSpeed MIDI
#define USEMULTIPLEX 0        // 1 = Usou multiplex para extender entradas; 0 = Não usou
#define ANALOGPINS 13         // Define a quantidade total de pinos analogicos conectados no Arduino/Multiplexador
#define DIGITALPINS 2         // Define a quantidade total de pinos digitais usados no projeto
#define PRESSETS 2            // Define a quantidade total de pressets carregados
////////////////////////

// Definir quais pinos digitais estão conectados os multiplexadores
#define MX1 30                // s0
#define MX2 31                // s1
#define MX3 32                // s2
#define MX4 33                // s3
// Definir quais pinos digitais estão conectados os botões de controle
# define CIMA 24
# define BAIXO 25
# define DIREITA 26
# define ESQUERDA 27
# define OK 28
# define BUTTONDEFAULTSTATE true  // se o botão for NF = true se for NA = false

/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// FIM DA CONFIGURAÇÃO MANUAL ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

//Determina a quantidade de pinos
const byte nPin = ANALOGPINS;
const byte nDpin = DIGITALPINS;

//Inicializa o LCD
LcdHandler handler = LcdHandler();

//Dados menu
bool readScan = false;
bool updateScreen = false;
byte midiChannel = 1;
byte hhControlSens = 5;
byte hhPin = 0;
byte hhControlPin = 0;
bool hhControlMode = true;  // CC or Mechanical
bool hhControlType = true;  // Analog or Digital
byte hhControlStages = 2;   // Qtd of notes
byte hhNote1 = 36;          // Open HH
byte hhNote2 = 36;          // Mid Open HH
byte hhNote3 = 36;          // Closed HH


//Listas de dados de Pinos Analógicos do Arduino
char* analogTypes[2] = {"Piezo", "Optical"};
char* digitalTypes[2] = {"Note", "Control"};


