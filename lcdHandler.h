// Handle all Liquid Crystal functions to be acessed quickly
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

class LcdHandler {
  String stringList[4] = {"", "", "", ""};

  public:
  LcdHandler() {}

  void setValues(String vals[]){
    for(int i = 0; i < 4; i++){
      stringList[i] = vals[i];
      printValue(i, stringList[i]);
    }
  }

  void replaceValue(int line, String val) {
    stringList[line] = val;
    printValue(line, val);
  }

  void pushOnTop(String val){
    for(int i = 3; i >= 0; i--){
      stringList[i] = stringList[i-1];
      printValue(i, stringList[i]);
    }
    stringList[0] = val;
    printValue(0, stringList[0]);
  }

  void pushOnBottom(String val){
    for(int i = 0; i< 3; i++){
      stringList[i] = stringList[i+1];
      printValue(i, stringList[i]);
    }
    stringList[3] = val;
    printValue(3, stringList[3]);
  }

  void indicatePosition(int line){
    for(int i=0; i<4; i++){
      if (i == line){
        replaceValue(i, ">" + stringList[i]);
      } else {
        stringList[i].replace(">", "");
        printValue(i, stringList[i]);
      }
    }
    lcd.setCursor(0, line);
    lcd.blink();
    delay(500);
  }


  private:
  void clearLine(int line){
    for (int i = 0; i < 20; i++){
      lcd.setCursor(i, line);
      lcd.print(" ");
    }
    lcd.setCursor(0, line);
  }

  void printValue(int line, String val) {
    clearLine(line);
    lcd.print(val);
  }
};