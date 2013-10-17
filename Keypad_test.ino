// LCD Library
#include <LiquidCrystal.h>
#include <Keypad.h>

// initialize LCD
LiquidCrystal lcd(23, 2, 3, 22, 4, 24);

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 53, 52, 51, 50 }; //left side corresponds to rows

byte colPins[COLS] = { 49, 48, 47, 46 }; // right corresponds to columns

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  lcd.begin(20,4);
}

void loop(){
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Welcome");
//  lcd.setCursor(0,1);
//  lcd.print("to");
//  lcd.setCursor(0,2);
//  lcd.print("The");
//  lcd.setCursor(0,3);
//  lcd.print("LCD");
//  delay(1000);
  
  char key = kpd.getKey();
  if(key !=NO_KEY)  // Check for a valid key.
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(key);
    delay(1000);
  }
}
