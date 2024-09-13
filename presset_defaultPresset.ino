// Default Presset
void defaultPresset(){
  // Global Instructions
  midiChannel = 1;                        // MIDI Channel Output
  hhPin = 0;                              // Hihat Pin index for Mechanical HHController
  hhControlPin = 0;                       // Hihat Control Pin for Mechanical HHController
  hhControlMode = true;                  // true = Control Change  false = Mechanical
  hhControlType = true;                   // true=Analog HHController  false=Digital HHController
  hhControlStages = 2;                    // Hihat Note Stages for HHController
  hhNote1 = 46;                           // Open HH Note
  hhNote2 = 42;                           // Mid Open HH Note
  hhNote3 = 42;                           // Closed HH Note
  // Pins Instructions
  Pin[0].set(A0, "HH Control", 4, 1);     // Pin[0-N].set(InputPin A0-A16(MEGA), "Name", Note 0-255, Type 0=Piezo 1=Optical|Potentiometer)
  Pin[0].setMuxChannel(0);                // Input = Arduino Input & muxChannel = Multiplexer Input Number
  Pin[0].isMultiplex = false;             // true=Enable Multiplex false=Not connected to multiplex
  // Digital Pins Instructions
  Dpin[0].set(22, "Choke1", 50, 0);        // Dpin[0-N].set(InputDigitalPin 2-53(MEGA), "Name", Note 0-255, Type 0=Note Play 1=Control)
  Dpin[0].setMuxChannel(0);               // Input = Arduino Input & muxChannel = Multiplexer Input Number
  Dpin[0].isMultiplex = false;            // true=Enable Multiplex false=Not connected to multiplex
  Dpin[0].maskTime = 50;                  // Minimum time before next note
  Dpin[0].defaultState = true;            // Default state of button NF = true | NA = false

  // Other Analog Pins
  Pin[1].set(A1, "Ride", 51, 0, true);
  Pin[2].set(A2, "Bell", 53, 0, true);
  Pin[3].set(A3, "Snare", 38, 0);
  Pin[4].set(A4, "Rim", 37, 0, true);
  Pin[5].set(A5, "Crash1", 49, 0);
  Pin[6].set(A6, "Crash2", 57, 0, true);
  Pin[7].set(A7, "Hihat", 42, 0);
  Pin[8].set(A8, "Splash", 55, 0, true);
  Pin[9].set(A9, "Kick", 36, 0);
  Pin[10].set(A10, "Tom1", 48, 0);
  Pin[11].set(A11, "Tom2", 45, 0);
  Pin[12].set(A11, "Floor", 41, 0);
  // Other Digital Pins
  Dpin[1].set(23, "Choke2", 56, 0);

  for(int i = 0; i<ANALOGPINS; i++){
    Pin[i].thresold = 20;
    Pin[i].scanTime = 10;
    Pin[i].maskTime = 30;
    Pin[i].retrigger = 30;
  }
}
