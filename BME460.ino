// BME 460 Game Panel Coding

// Define Input/Out

// LCD Library
#include <LiquidCrystal.h>

// initialize LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Define Button Signifiers
#define btnNONE 0
#define btnSELECT 1
#define btnLEFT 2
#define btnDOWN 3
#define btnUP 4
#define btnRIGHT 5

// Define Voltage Thresholds for each Button
#define vSELECT 3.5
#define vLEFT 2.5
#define vDOWN 1.5
#define vUP 0.75
#define vRIGHT 0.25

void setup()
{
  // Setup LCD
  lcd.begin(16, 2);

  // Setup Input/Output Pins
  
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("Client Name");
  delay (5000);
  
  Game();
  
}
