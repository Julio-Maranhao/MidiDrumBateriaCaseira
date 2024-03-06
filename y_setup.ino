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
  // Ativa o multiplexador
  # if USEMULTIPLEX
    multiplex.setMultiplex();
  # endif

  // Set main menu
  mainMenu.init();

  // Setar Botoes de Conctrole
  Buttons[0].set(OK, BUTTONDEFAULTSTATE);
  Buttons[1].set(CIMA, BUTTONDEFAULTSTATE);
  Buttons[2].set(BAIXO, BUTTONDEFAULTSTATE);
  Buttons[3].set(DIREITA, BUTTONDEFAULTSTATE);
  Buttons[4].set(ESQUERDA, BUTTONDEFAULTSTATE);

  pinMode(OK, INPUT_PULLUP);
  pinMode(CIMA, INPUT_PULLUP);
  pinMode(BAIXO, INPUT_PULLUP);
  pinMode(DIREITA, INPUT_PULLUP);
  pinMode(ESQUERDA, INPUT_PULLUP);
  // Carrega o presset default
  defaultPresset();
}
