// Freeplay

void Freeplay(){
  digitalWrite(irqpin, HIGH);
  digitalWrite(buttonin, HIGH);
  digitalWrite(pushin, HIGH);
  digitalWrite(joystickin, HIGH);
  digitalWrite(spinin, HIGH);
  digitalWrite(pullin, HIGH);

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
//  else if (IRdetect >= 50){
//    bballresponse();
//  }
  else if (buttonsense == HIGH){
    buttonresponse();
  }
  else if (pushsense <= 500){
    pushresponse();
  }
  else if (joysticksense >= 700){
    joystickresponse();
  }
  else if (spinsense >= 600){
    
      spinresponse();
  }
  else if (pullsense >= 550){
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
//  digitalWrite(car1, HIGH);
//  digitalWrite(sound1, HIGH);
//  delay(3000);
//  digitalWrite(car1, LOW);
//  digitalWrite(sound1, LOW);
}

// button response

void buttonresponse(){
  LEDresponse(2);
  digitalWrite(sound1, HIGH);
  delay(1000);
  digitalWrite(sound1, LOW);
//  digitalWrite(car1, HIGH);
//  delay(3000);
//  digitalWrite(car1, LOW);
}

// push response

void pushresponse(){
  LEDresponse(3);
//  digitalWrite(car2, HIGH);
//  digitalWrite(sound1,HIGH);
//  delay(3000);
//  digitalWrite(car2, LOW);
//  digitalWrite(sound1,LOW);
}

// joystick response

void joystickresponse(){
  LEDresponse(4);
//  digitalWrite(car1, HIGH);
//  digitalWrite(car2, HIGH);
//  delay(3000);
//  digitalWrite(car1, LOW);
//  digitalWrite(car2, LOW);
}

// spin response

void spinresponse(){
  LEDresponse(5);
//  digitalWrite(car2, HIGH);
//  delay(3000);
//  digitalWrite(car2, LOW);
}

// pull response

void pullresponse(){
  LEDresponse(6);
//  digitalWrite(car2, HIGH);
////  digitalWrite(fan,HIGH);
//  delay(3000);
//  digitalWrite(car2, LOW);
////  digitalWrite(fan,LOW);
}

// basketball response

void bballresponse(){
  LEDresponse(7);
////  digitalWrite(fan, HIGH);
//  digitalWrite(car1, HIGH);
//  digitalWrite(car1, HIGH);
//  delay(3000);
////  digitalWrite(fan, LOW);
//  digitalWrite(car1, LOW);
//  digitalWrite(car1, LOW);
}

//LED response

void LEDresponse(int LED){

  switch(LED){

  case 1:
    {
      send_1M_pattern(pattern_test_red, 10, 500);
      delay(500);
    }

  case 2:
    {
      send_1M_pattern(pattern_test_blue, 10, 500);
      delay(500);
    }

  case 3:
    {
      send_1M_pattern(pattern_test_green, 10, 500);
      delay(500);
    }

  case 4:
    {
      send_1M_pattern(pattern_test_comet4, 10, 500);
      delay(500);
    }
  case 5:
    {
      send_1M_pattern(pattern_test_comet5, 10, 500);
      delay(500);
    }

  case 6:
    {
      send_1M_pattern(pattern_test_comet2, 10, 500);
      delay(500);
    }

  case 7:
    {
      send_1M_pattern(pattern_test_comet3, 10, 500);
      delay(500);
    }
  case 8:
    {
      send_1M_pattern(pattern_test_comet4, 10, 500);
      delay(500);
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


