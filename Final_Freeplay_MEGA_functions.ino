// Freeplay

void Freeplay(){
  digitalWrite(irqpin, HIGH);
  digitalWrite(buttonin, HIGH);
  digitalWrite(pushin, HIGH);
  digitalWrite(joystickin, HIGH);
  digitalWrite(spinin, HIGH);
  digitalWrite(pullin, HIGH);
  
int bballsense=analogRead(IRdetect);
int buttonsense=analogRead(buttonout);
int pushsense=analogRead(pushout);
int joysticksense=analogRead(joystickout);
int spinsense=analogRead(spinout);
int pullsense=analogRead(pullout);
delay(50);
int spinsense2=analogRead(spinout);
int pullsense2=analogRead(pullout);



  if(!checkInterrupt()){

    Wire.requestFrom(0x5A,2); 

    byte LSB = Wire.read();
    byte MSB = Wire.read();

    uint16_t touched = ((MSB << 8) | LSB);

    int touchStates[12];
    int i;

    for (i=0; i < 2; i++){ 
      if(touched & (1<<i)){

        if(touchStates[i] == 0){

          switch(i){
          case 0:
            touchresponse();
            break;

          case 1:
            touchresponse();
            break;

          }

        }
        else if(touchStates[i] == 1){
        }  

        touchStates[i] = 1;      
      }
      else{
        if(touchStates[i] == 1){
        }

        touchStates[i] = 0;
      }

    }

  }
  else if (bballsense >= 25){
    bballresponse();
  }
  else if (buttonsense >= 300){
    buttonresponse();
  }
  else if (pushsense >= 600){
    pushresponse();
  }
  else if (joysticksense >= 300){
    joystickresponse();
  }
  else if (spinsense != spinsense2 && spinsense != spinsense2+1 && spinsense != spinsense2-1 && spinsense != spinsense2+2 && spinsense != spinsense2-2 && spinsense != spinsense2+3 && spinsense != spinsense2-3){// && spinsense != spinsense2-4 && spinsense != spinsense2+4 && spinsense != spinsense2-5 && spinsense !=spinsense2+5){    
      spinresponse();
  }
  else if (pullsense-pullsense2>=25 || pullsense2-pullsense>=25){
    pullresponse();
  }
}

// mpr121 setup

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

  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(0x5A, FIL_CFG, 0x04);

  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(0x5A, ELE_CFG, 0x02); 


  // Section F
  // Enable Auto Config and auto Reconfig

  set_register(0x5A, ELE_CFG, 0x02);

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

// touch response

void touchresponse(){
  LEDresponse(1);
  analogWrite(car1, 375);
  digitalWrite(sound1, HIGH);
  delay(1000);
  digitalWrite(car1, LOW);
  digitalWrite(sound1, LOW);
}

// button response

void buttonresponse(){
  LEDresponse(2);
  digitalWrite(sound1, HIGH);
  digitalWrite(fan, HIGH);
  delay(3000);
  digitalWrite(fan, LOW);
  digitalWrite(sound1, LOW);
}

// push response

void pushresponse(){
  LEDresponse(3);
  analogWrite(car2, 400);
  digitalWrite(sound2,HIGH);
  delay(1000);
  digitalWrite(car2, LOW);
  digitalWrite(sound2,LOW);
}

// joystick response

void joystickresponse(){
  LEDresponse(5);
  digitalWrite(sound1, HIGH);
  analogWrite(car2, 400);
  delay(1000);
  digitalWrite(car2, LOW);
  digitalWrite(sound1, LOW);
}

// spin response

void spinresponse(){
  LEDresponse(6);
  analogWrite(car1, 375);
  digitalWrite(sound2,HIGH);
  delay(1000);
  digitalWrite(car1, LOW);
  digitalWrite(sound2,LOW);
//  digitalWrite(car1, HIGH);
//  delay(1000);
//  digitalWrite(car1, LOW);
}

// pull response

void pullresponse(){
  LEDresponse(8);

  digitalWrite(fan, HIGH);
  digitalWrite(sound2,HIGH);
  delay(3000);
  digitalWrite(fan, LOW);
  digitalWrite(sound2,LOW);
}

// basketball response

void bballresponse(){
  LEDresponse(7);
  digitalWrite(fan, HIGH);
  delay(5000);
  digitalWrite(fan, LOW);
}

//LED response

void LEDresponse(int LED){

  switch(LED){

  case 1:
    {
      send_1M_pattern(pattern_test_red, 10, 150);
      delay(500);
      break;
    }

  case 2:
    {
      send_1M_pattern(pattern_test_blue, 10, 150);
      delay(500);
      break;
    }

  case 3:
    {
      send_1M_pattern(pattern_test_green, 10, 150);
      delay(500);
      break;
    }

  case 4:
    {
      send_1M_pattern(pattern_test_purple, 10, 150);
      delay(500);
      break;
    }
  case 5:
    {
      send_1M_pattern(pattern_test_yellow, 10, 150);
      delay(500);
      break;
    }

  case 6:
    {
      send_1M_pattern(pattern_test_white, 10, 150);
      delay(500);
      break;
    }

  case 7:
    {
      send_1M_pattern(pattern_test_pink, 10, 150);
      delay(500);
      break;
    }
  case 8:
    {
      send_1M_pattern(pattern_test_cyan, 10, 150);
      delay(500);
      break;
    }
  }
}

/*******************************************************************************
 * Function Name  : send_1M_pattern
 * Description    : Transmit pattern to whole 1 meter strip
 *                  
 * Input          : pointer to ROM pattern; pattern length; frame rate
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_1M_pattern(const unsigned long data[][10], int pattern_no, int frame_rate)
{
  int i=0;
  int j=0;
  uint32_t temp_data;

  for (i=0;i<pattern_no;i++)
  {
    noInterrupts();
    for (j=0;j<10;j++)
    {
      temp_data=pgm_read_dword_near(&data[i][j]);
      send_strip(temp_data);
    }
    interrupts();

    delay(frame_rate);

  }




}


/*******************************************************************************
 * Function Name  : send_strip
 * Description    : Transmit 24 pulse to LED strip
 *                  
 * Input          : 24-bit data for the strip
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_strip(uint32_t data)
{
  int i;
  unsigned long j=0x800000;


  for (i=0;i<24;i++)
  {
    if (data & j)
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");

      /*----------------------------*/
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");  
      __asm__("nop\n\t");        
      /*----------------------------*/
      DATA_0;
    }
    else
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      DATA_0;
      /*----------------------------*/
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");      
      /*----------------------------*/
    }

    j>>=1;
  }



}

/*******************************************************************************
 * Function Name  : reset_strip
 * Description    : Send reset pulse to reset all color of the strip
 *                  
 * Input          : None
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void	reset_strip()
{
  DATA_0;
  delayMicroseconds(20);
}

// LCD

void lcdPosition(int row, int col) {
LCD.write(0xFE); //command flag
LCD.write((col + row*64 + 128)); //position
delay(LCDdelay);
}

//void lcdPositionLine1() {
//LCD.write(0xFE); //command flag
//LCD.write(0x45);
//LCD.write(0x00);
//delay(LCDdelay);
//}

void lcdPositionLine2() {
LCD.write(0xFE); //command flag
LCD.write(0x45);
LCD.write(0x40);
delay(LCDdelay);
}

void lcdPositionLine3() {
LCD.write(0xFE); //command flag
LCD.write(0x45);
LCD.write(0x14);
delay(LCDdelay);
}

void lcdPositionLine4() {
LCD.write(0xFE); //command flag
LCD.write(0x45);
LCD.write(0x54);
delay(LCDdelay);
}

void clearLCD(){
LCD.write(0xFE); //command flag
LCD.write(0x51); //clear command.
delay(LCDdelay);
}

void serCommand(){ //a general function to call the command flag for issuing all other commands
LCD.write(0xFE);
}

void setLCDContrast() {
LCD.write(0xFE); //command flag
LCD.write(0x52);
LCD.write(40); //value 1 to 50 (50 is highest contrast)
delay(LCDdelay);
}

void setLCDBrightness() {
LCD.write(0xFE); //command flag
LCD.write(0x53);
LCD.write(8); //value 1 to 8
delay(LCDdelay);
}

