## MIDI DRUM BATERIA COM ARDUINO 👨‍💻

#### 1. Compatible Arduinos
- Arduino MEGA;
- Arduino Pro Micro;
- Arduino UNO;
- Any other Arduino that can turn into a MIDI USB device;

#### 2. Requirements
For Arduino Pro Micro it requires MIDI library at "MidiDrumBateriaCaseira.ino" like it follows:
``` cpp
// Arduino PRO MICRO
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
```

<p>For other Arduinos that use AtMega16u2 as USB handler we need <a href="https://github.com/kuwatay/mocolufa">MocoLufa</a> procedure to be able to read as a USB MIDI device.</p>

At last you need to know how to wire and build your own drum controller with piezos, buttons and potentiometers or optical sensors to use this code.

#### 3. GetStarted

First of all, lets adjust main settings at "MidiDrumBateriaCaseira.ino":

```cpp
///// CONFIGURATION /////
#define USEMIDI 1             // 0 = 115200 SerialSpeed; 1 = 31250 SerialSpeed MIDI
#define USEMULTIPLEX 0        // 1 = Analog or Digital Multiplexer 4bits; 0 = None
#define ANALOGPINS 13         // Analog Pins Connected
#define DIGITALPINS 2         // Digital Pins Connected
#define MIDIMAPS 7            // Midi Maps Created
////////////////////////

// Definie Arduino pins connected to Multiplexer
#define MX1 30                // s0 pin
#define MX2 31                // s1 pin
#define MX3 32                // s2 pin
#define MX4 33                // s3 pin
// Define Arduino pins assigned as control buttons for Menu navigation
# define CIMA 24              // up
# define BAIXO 25             // down
# define DIREITA 26           // right
# define ESQUERDA 27          // left
# define OK 28                // ok
# define BUTTONDEFAULTSTATE true  // button's defult state open=false closed=true
```

The recomendation to number of digital pins is 32 at most while digital pins is 16 at most.

Then at "lcdHandler.h" we need to start liquidCrystal by sending the connection as I2C or normal wiring.
- Normal Wiring
    > lcdHandler.h
    ```cpp
    ///////////// lcd(RS, E, DB4, DB5, DB6, DB7) - LCD pins
    LiquidCrystal lcd(12, 11, 6, 5, 4, 3); // Arduino pins connected
    ```

    >y_setup.ino
    ```cpp
    lcd.init(20,4);   // LCD 20x4 20 columns and 4 rows
    ```
- I2C wiring
    > lcdHandler.h
    ```cpp
    ///////////// lcd(channel, Columns, Rows)
    LiquidCrystal lcd(0x27 20, 4);
    ```

    >y_setup.ino
    ```cpp
    lcd.init();   // Already set Columns and Rows
    ```

#### 4. MIDI Maps
Default MIDI map uses Arduino's EEPROM memory to store Global Settings, Analog Pins data and Digital Pins data. For better use Change all MidiMaps/MidiPressets to Match your current ANALOGPINS and DIGITALPINS number.

If you want to add more or remove these you need to adjust the "x_pressets.ino" document and MIDIMAPS number.
```cpp
String getPresset(int num){
  switch(num) {
    case 0:
      return "Default";
      break;
    case 1:
      return "Real Drums APP";
      break;
    ...
    // Add presset
    //case up + 1:
    //  return "presset name"
    //  break;
    case 7:
      return "Save to Memory";
      break;
    case 8:
      return "Load from Memory";
      break;
    
    default:
      return "--------------------";
  }
}

void setPresset(int num){
  switch(num) {
    case 0:
      defaultPresset();
      break;
    case 1:
      realDrum();
      break;
    ...
    // Add presset
    //case up+1:
    //  presetFunction();
    //  break;
    case 7:
      saveGlobalConfigs();
      break;
    case 8:
      loadGlobalConfigs();
      break;
    default:
      return;
  }
}
```
theese last ones for Save and Load need to be there at any position just make shure that **last switch case is MIDIMAPS + 1.**

All "presset_xxx.ino" are made using the structure to add Pins:
```cpp
Pin[Number].set(Input, "Name", Note, Type, isDisabled); // AnalogPin
Dpin[Number].set(Input, "Name", Note, Type, isDisabled); // Digital Pin
// Last Number shoud be ANALOGPINS - 1 for Analog or DIGITALPINS - 1 for Digital
```

#### 5. AnalogPins Configuration
At Menu > Settings > Analog pins. You can edit all these parameters for analog pins to match your play.
- **Input:** Arduino's pin connected, Multiplex signal connected if multiplexer
- **Mux Channel:** Multiplexer's Input channel
- **Curve:** Actuation curve A=Log, B=Exp, C=Linear for MIDI volume
- **Type:** 1 = Note/Piezo, 2 = ControlChange/Optical/Potenciometer
- **Name:** Name for this pin
- **Note:** MIDI note
- **Mask Time:** Minimum time in miliseconds for repeated notes
- **Min Sens:** Minimum strike required to play note, the more the less sensitive 0 - 1024
- **Max Sens:** Strike required to play at max volume 0 - 1024
- **Gain:** Minimum volume to play 0 - 127
- **Is Multiplex:** false - Not multiplex, true - Multiplexer Connected
- **Is Disabled:** false - Available to play, true - Unavailable

#### 6. DigitalPins Configuration
At Menu > Settings > Digital pins. You can edit all these parameters for digital pins to match your play.
- **Input:** Arduino's pin connected, Multiplex signal connected if multiplexer
- **Mux Channel:** Multiplexer's Input channel
- **Type:** 1 = Note, 2 = ControlChange
- **Name:** Name for this pin
- **Note:** MIDI note
- **Mask Time:** Minimum time in miliseconds for repeated notes
- **Default State:** false - Closed, true - Open
- **Is Multiplex:** false - Not multiplex, true - Multiplexer Connected
- **Is Disabled:** false - Available to play, true - Unavailable

### 7. Global Settings
Global settings defines Hihat control type and sensitivenes, MIDI channel used to send notes. There are two modes in this code Mechanical (code for changing Hihat notes) and Control Change (software controlling Hihat).

- **Midi Channel** Current Midi channel to play
- **HH Control Sens** Sensitivity of Hihat control the more the lass
- **HH pin** Number of Hihat control Pin for mechanical change
- **HH Control Mode** true = Control Change, false = mechanical
- **HH Control Type** true = Analog Control, false = Digital Control
- **HH Control Stages** Number of Hihat Notes to change 2 or 3
- **Hihat Open Note** Note when Hihat is Open at Mechanical
- **Hihat MidOpen Note** Note when Hihat is Mid Open at Mechanical
- **Hihat Closed Note** Note when Hihat is Closed at Mechanical