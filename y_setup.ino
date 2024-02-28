void setup()
{
  //Define o LCD com 20 colunas e 4 linhas
  lcd.begin(20, 4);
  //Inicia o Serial
  # if USEMIDI
    Serial.begin(31250);
  # else
    Serial.begin(115200);
  # endif

  # if USEMULTIPLEX
    multiplex.setMultiplex();
  # endif

  // Set Pin Info for Settings
  for(int i = 0; i<ANALOGPINS; i++){
    inputList[i] = A0 + 1;
    inputNames[i] = "A" + String(i);
  }
  
  //Mostra informacoes no display
  lcd.print("Hello World");
  for(int button : buttons) {
    pinMode(button, INPUT_PULLUP);
  }
  
  Pin[0].set(ANALOG12, "Kick", 36, 2);
}
