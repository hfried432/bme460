#include <Keypad.h>
#include <mpr121.h>
#include <Wire.h>
#include <LiquidCrystal.h>


int irqpin = 37;// Digital 37
// touch works
int touchre= 12;
//bball works but touch sensor is not sensitive enough
int bballre=9;
// button works
int buttonin= 38;
int buttonout= 32;
int buttonre= 11;
// push works
int pushin= 36;
int pushout= A1;
int pushre= 13;
// joystick works but is very sensitive
int joystickin= 50;
int joystickout1= A8;
int joystickout2= A9;
int joystickout3= A10;
int joystickout4= A11;
int joystickre= 5;
// we need to use greater than as opposed to less than, need to work with magnets
int spinin= 52;
int spinout= A6;
int spinre= 7;
//pull works
int pullin= 51;
int pullout= A14;
int pullre= 4;

boolean touchStates[12]; //to keep track of the previous touch states

LiquidCrystal lcd(47, 46, 45, 41, 44, 43);

void setup(){
  pinMode(irqpin, INPUT);
  pinMode(touchre,OUTPUT);
  pinMode(bballre, OUTPUT);
  digitalWrite(irqpin, HIGH); //enable pullup resistor
  pinMode(buttonin, OUTPUT);
  pinMode(buttonout, INPUT);
  pinMode(buttonre, OUTPUT);
  digitalWrite(buttonin, HIGH);
  pinMode(pushin, OUTPUT);
  pinMode(pushout, INPUT);
  pinMode(pushre, OUTPUT);
  digitalWrite(pushin, HIGH);
  pinMode(joystickin, OUTPUT);
  pinMode(joystickout1, INPUT);
  pinMode(joystickout2, INPUT);
  pinMode(joystickout3, INPUT);
  pinMode(joystickout4, INPUT);
  pinMode(joystickre, OUTPUT);
  digitalWrite(joystickin, HIGH);
  pinMode(spinin, OUTPUT);
  pinMode(spinout, INPUT);
  pinMode(spinre, OUTPUT);
  digitalWrite(spinin, HIGH);
  pinMode(pullin, OUTPUT);
  pinMode(pullout, INPUT);
  pinMode(pullre, OUTPUT);
  digitalWrite(pullin, HIGH);
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
  Freeplay();
}


void Freeplay(){
  int buttonsense=digitalRead(buttonout);
  int pushsense=analogRead(pushout);
  int joysticksense1=analogRead(joystickout1);
  int joysticksense2=analogRead(joystickout2);
  int joysticksense3=analogRead(joystickout3);
  int joysticksense4=analogRead(joystickout4);
  int spinsense=analogRead(spinout);
  int pullsense=analogRead(pullout);
  
  if(!checkInterrupt()){
    
    //read the touch state from the MPR121
    Wire.requestFrom(0x5A,2); 
    
    byte LSB = Wire.read();
    byte MSB = Wire.read();
    
    uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states
    
    int touchStates[12];
    int i;
    
    for (i=0; i < 3; i++){  // Check what electrodes were pressed
      if(touched & (1<<i)){
      
        if(touchStates[i] == 0){
          //pin i was just touched
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("pin");
            lcd.setCursor(0,1);
            lcd.print(i);
            lcd.setCursor(0,2);
            lcd.print("was just touched");
            
            switch(i){
              case 0:
              digitalWrite(2,HIGH);
              delay(300);
              digitalWrite(2,LOW);
              digitalWrite(touchre, HIGH);
              delay(3000);
              digitalWrite(touchre, LOW);
              break;
            
              case 1:
              digitalWrite(2,HIGH);
              delay(300);
              digitalWrite(2,LOW);
              digitalWrite(touchre,HIGH);
              delay(3000);
              digitalWrite(touchre, LOW);
              break;
            
              case 2:
              digitalWrite(2,HIGH);
              delay(300);
              digitalWrite(2,LOW);
              digitalWrite(bballre, HIGH);
              delay(3000);
              digitalWrite(bballre, LOW);
              break;
            
          }
        
        }else if(touchStates[i] == 1){
        }  
      
        touchStates[i] = 1;      
      }else{
        if(touchStates[i] == 1){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("pin ");
          lcd.setCursor(0,1);
          lcd.print(i);
          lcd.setCursor(0,2);
          lcd.print("is no longer");
          lcd.setCursor(0,3);
          lcd.print("being touched");
//          
//          //pin i is no longer being touched
       }
        
        touchStates[i] = 0;
      }
    
    }
    
  }else if (buttonsense == HIGH){
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    digitalWrite(buttonre, HIGH);
    delay(3000);
    digitalWrite(buttonre, LOW);
  }else if (pushsense <= 500 & pushsense >= 100){
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    digitalWrite(pushre, HIGH);
    delay(3000);
    digitalWrite(pushre, LOW);
  }else if (joysticksense1>=700){
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    digitalWrite(joystickre, HIGH);
    delay(3000);
    digitalWrite(joystickre, LOW);
  }else if (joysticksense2>=700){
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    digitalWrite(joystickre, HIGH);
    delay(3000);
    digitalWrite(joystickre, LOW);
  }else if (joysticksense3>=700){
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    digitalWrite(joystickre, HIGH);
    delay(3000);
    digitalWrite(joystickre, LOW);
  }else if (joysticksense4>=700){
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);  
    digitalWrite(joystickre, HIGH);
    delay(3000);
    digitalWrite(joystickre, LOW);
  }else if (spinsense >= 500){
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    digitalWrite(spinre, HIGH);
    delay(3000);
    digitalWrite(spinre, LOW);
  }else if (pullsense >= 500){
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    digitalWrite(pullre, HIGH);
    delay(3000);
    digitalWrite(pullre, LOW);
  }
}




void mpr121_setup(void){

  set_register(0x5A, ELE_CFG, 0x00); 
  
  // Section A - Controls filtering when data is > baseline.
  set_register(0x5A, MHD_R, 0x01);
  set_register(0x5A, NHD_R, 0x01);
  set_register(0x5A, NCL_R, 0x00);
  set_register(0x5A, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(0x5A, MHD_F, 0x01);
  set_register(0x5A, NHD_F, 0x01);
  set_register(0x5A, NCL_F, 0xFF);
  set_register(0x5A, FDL_F, 0x02);
  
  // Section C - Sets touch and release thresholds for each electrode
  set_register(0x5A, ELE0_T, TOU_THRESH);
  set_register(0x5A, ELE0_R, REL_THRESH);
 
  set_register(0x5A, ELE1_T, TOU_THRESH);
  set_register(0x5A, ELE1_R, REL_THRESH);
  
  set_register(0x5A, ELE2_T, TOU_THRESH);
  set_register(0x5A, ELE2_R, REL_THRESH);
  
  set_register(0x5A, ELE3_T, TOU_THRESH);
  set_register(0x5A, ELE3_R, REL_THRESH);
  
//  set_register(0x5A, ELE4_T, TOU_THRESH);
//  set_register(0x5A, ELE4_R, REL_THRESH);
//  
//  set_register(0x5A, ELE5_T, TOU_THRESH);
//  set_register(0x5A, ELE5_R, REL_THRESH);
//  
//  set_register(0x5A, ELE6_T, TOU_THRESH);
//  set_register(0x5A, ELE6_R, REL_THRESH);
//  
//  set_register(0x5A, ELE7_T, TOU_THRESH);
//  set_register(0x5A, ELE7_R, REL_THRESH);
//  
//  set_register(0x5A, ELE8_T, TOU_THRESH);
//  set_register(0x5A, ELE8_R, REL_THRESH);
//  
//  set_register(0x5A, ELE9_T, TOU_THRESH);
//  set_register(0x5A, ELE9_R, REL_THRESH);
//  
//  set_register(0x5A, ELE10_T, TOU_THRESH);
//  set_register(0x5A, ELE10_R, REL_THRESH);
//  
//  set_register(0x5A, ELE11_T, TOU_THRESH);
//  set_register(0x5A, ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(0x5A, FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(0x5A, ELE_CFG, 0x03);  // Enables all 12 Electrodes
  
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(0x5A, ATO_CFG0, 0x0B);
  set_register(0x5A, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5A, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(0x5A, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
  set_register(0x5A, ELE_CFG, 0x03);
  
}


boolean checkInterrupt(void){
  return digitalRead(irqpin);
}


void set_register(int address, unsigned char r, unsigned char v){
    Wire.beginTransmission(address);
    Wire.write(r);
    Wire.write(v);
    Wire.endTransmission();
}
