#include <Keypad.h>
#include <mpr121.h>
#include <Wire.h>
#include <LiquidCrystal.h>


int irqpin = 37;
int touchre= 12;
int bballre=9;
int buttonin= 38;
int buttonout= 32;
int buttonre= 11;
int pushin= 36;
int pushout= A1;
int pushre= 13;
int joystickin= 50;
int joystickout= 3;
int joystickre= 5;
int spinin= 52;
int spinout= A6;
int spinre= 7;
int pullin= 51;
int pullout= A14;
int pullre= 4;

int buttonsense=digitalRead(buttonout);
int pushsense=analogRead(pushout);
int joysticksense=analogRead(joystickout);
int spinsense=analogRead(spinout);
int pullsense=analogRead(pullout);

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 28, 29, 26, 27 }; //left side corresponds to rows

byte colPins[COLS] = { 24, 25, 22, 23 }; // right corresponds to columns

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

boolean touchStates[12];

LiquidCrystal lcd(47, 46, 45, 41, 44, 43);

void setup(){
  pinMode(irqpin, INPUT);
  pinMode(touchre,OUTPUT);
  pinMode(bballre, OUTPUT);
  pinMode(buttonin, OUTPUT);
  pinMode(buttonout, INPUT);
  pinMode(buttonre, OUTPUT);
  pinMode(pushin, OUTPUT);
  pinMode(pushout, INPUT);
  pinMode(pushre, OUTPUT);
  pinMode(joystickin, OUTPUT);
  pinMode(joystickout, INPUT);
  pinMode(joystickre, OUTPUT);
  pinMode(spinin, OUTPUT);
  pinMode(spinout, INPUT);
  pinMode(spinre, OUTPUT);
  pinMode(pullin, OUTPUT);
  pinMode(pullout, INPUT);
  pinMode(pullre, OUTPUT);
  pinMode(2,OUTPUT);
  
  lcd.begin(20,4);
  Wire.begin();

  mpr121_setup();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("Client Name");
  delay (5000);
}

void loop(){
  Game();
}
