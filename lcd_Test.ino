// LCD Library
#include <LiquidCrystal.h>


// initialize LCD
LiquidCrystal lcd(7, 9, 10, 11, 12, 13);

void setup(){
  lcd.begin(20,4);
}

void loop(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("to");
  lcd.setCursor(0,2);
  lcd.print("The");
  lcd.setCursor(0,3);
  lcd.print("LCD");
  delay(4000);
  
}
