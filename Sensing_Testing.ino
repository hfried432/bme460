int inpin = 42;
int outpin = 43;

// LCD Library
#include <LiquidCrystal.h>

// initialize LCD
LiquidCrystal lcd(23, 2, 3, 22, 4, 24);

void setup()
{
  // Setup LCD
  lcd.begin(20, 4);

  // Setup Input/Output Pins
  pinMode(inpin, INPUT);
  pinMode(outpin, OUTPUT);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Start");
  delay(1000);
  
  int value = actiond();
  
}
