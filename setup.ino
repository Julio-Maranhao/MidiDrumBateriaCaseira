void setup()
{
  //Define o LCD com 20 colunas e 4 linhas
  //lcd.begin(20, 4);
  lcd.begin(20, 4);
  //Inicia o Serial
  # if USEMIDI
    Serial.begin(31250);
  # else
    Serial.begin(115200);
  # endif
  
  //Mostra informacoes no display
  lcd.print("Hello World");
  for(int button : buttons) {
    pinMode(button, INPUT_PULLUP);
  }

  Pin[0].set(ANALOG12, "chama", 36, 4);
}