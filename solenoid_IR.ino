#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){
  
  pinMode(12,OUTPUT);
  pinMode(A1,INPUT);
  pinMode(2,OUTPUT);
  delay(3000);
  
  lcd.begin(14,2);
}

void loop(){
  
  int aread=analogRead(A1);
  
  lcd.clear();
  lcd.print(aread);
  delay(1000);
  
  if (aread>=510){
    digitalWrite(12,HIGH); 
    digitalWrite(2,HIGH);
    delay(5000);
    digitalWrite(12,LOW);
    digitalWrite(2,LOW);
    delay(1000);
  }
}
