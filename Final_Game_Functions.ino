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

    for (i=0; i < 3; i++){ 
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
  else if (buttonsense == HIGH){
    buttonresponse();
  }
  else if (pushsense <= 500 & pushsense >= 100){
    pushresponse();
  }
  else if (joysticksense>=900){
    joystickresponse();
  }
  else if (spinsense >= 550){
    spinresponse();
  }
  else if (pullsense >= 500){
    pullresponse();
  }
}

// Easy Game

void easygame(int score, int GetGame){
  int totaltime=millis();
  if (totaltime>=90000){
    totaltime=0;
    Replay(GetGame);
  }
  else{
    if (score>=3){
      digitalWrite(bballre, HIGH);
      delay(2000);
      digitalWrite(bballre,LOW);
      score=0;
      easygame(score, GetGame);
    }
    else{
      int Easy=random(1,2);

      switch(Easy){
      case 1:
        {
          digitalWrite(buttonin, HIGH);
          int time=millis();
          if (buttonsense==HIGH){
            buttonresponse();
            time=0;
            score=score+1;
          }
          else if (time>=15000){
            time=0;
            score=0;
          }
          break;
        }

      case 2:
        {
          digitalWrite(spinin, HIGH);
          int time=millis();
          if (spinsense>= 550){
            spinresponse();
            time=0;
            score=score+1;
          }
          else if (time>=1500){
            time=0;
            score=0;
          }
          break;
        }
      }
      easygame(score, GetGame);
    }
  }
}

// Medium Game

void medgame(int score, int GetGame){
  int totaltime=millis();
  if (totaltime>=90000){
    totaltime=0;
    Replay(GetGame);
  }
  else{
    if (score>=3){
      digitalWrite(bballre, HIGH);
      delay(2000);
      digitalWrite(bballre,LOW);
      score=0;
      medgame(score, GetGame);
    }
    else{
      int Med=random(1,4);

      switch(Med){
      case 1:
        {
          digitalWrite(buttonin, HIGH);
          int time=millis();
          if (buttonsense==HIGH){
            buttonresponse();
            time=0;
            score=score+1;
          }
          else if (time>=15000){
            time=0;
            score=0;
          }
          break;
        }

      case 2:
        {
          digitalWrite(spinin, HIGH);
          int time=millis();
          if (spinsense>= 550){
            spinresponse();
            time=0;
            score=score+1;
          }
          else if (time>=1500){
            time=0;
            score=0;
          }
          break;
        }

      case 3:
        {
          digitalWrite(joystickin, HIGH);
          int time=millis();
          if (joysticksense>=900){
            joystickresponse();
            time=0;
            score=score+1;
          }
          else if (time>=15000){
            time=0;
            score=0;
          }
          break;
        }

      case 4:
        {
          digitalWrite(pushin, HIGH);
          int time=millis();
          if (pushsense <= 500 & pushsense >= 100){
            pushresponse();
            time=0;
            score=score+1;
          }
          else if (time>=1500){
            time=0;
            score=0;
          }
          break;
        }
      }
      medgame(score, GetGame);
    }
  }
}

// Hard Game

void hardgame(int score, int GetGame){
  int totaltime=millis();
  if (totaltime>=90000){
    totaltime=0;
    Replay(GetGame);
  }
  else{
    if (score>=3){
      digitalWrite(bballre, HIGH);
      delay(2000);
      digitalWrite(bballre,LOW);
      score=0;
      hardgame(score, GetGame);
    }
    else{
      int Hard=random(1,6);

      switch(Hard){
      case 1:
        {
          digitalWrite(buttonin, HIGH);
          int time=millis();
          if (buttonsense==HIGH){
            buttonresponse();
            time=0;
            score=score+1;
          }
          else if (time>=15000){
            time=0;
            score=0;
          }
          break;
        }

      case 2:
        {
          digitalWrite(spinin, HIGH);
          int time=millis();
          if (spinsense>= 550){
            spinresponse();
            time=0;
            score=score+1;
          }
          else if (time>=1500){
            time=0;
            score=0;
          }
          break;
        }

      case 3:
        {
          digitalWrite(joystickin, HIGH);
          int time=millis();
          if (joysticksense>=900){
            joystickresponse();
            time=0;
            score=score+1;
          }
          else if (time>=15000){
            time=0;
            score=0;
          }
          break;
        }

      case 4:
        {
          digitalWrite(pushin, HIGH);
          int time=millis();
          if (pushsense <= 500 & pushsense >= 100){
            pushresponse();
            time=0;
            score=score+1;
          }
          else if (time>=1500){
            time=0;
            score=0;
          }
          break;
        }

      case 5:
        {
          digitalWrite(pullin, HIGH);
          int time=millis();
          if (pullsense >= 500){
            pullresponse();
            time=0;
            score=score+1;
          }
          else if (time>=15000){
            time=0;
            score=0;
          }
          break;
        }

      case 6:
        {
          digitalWrite(irqpin, HIGH);
          int time=millis();
          if(!checkInterrupt()){

            Wire.requestFrom(0x5A,2); 

            byte LSB = Wire.read();
            byte MSB = Wire.read();

            uint16_t touched = ((MSB << 8) | LSB);

            int touchStates[12];
            int i;

            for (i=0; i < 3; i++){ 
              if(touched & (1<<i)){

                if(touchStates[i] == 0){

                  switch(i){
                  case 0:
                    touchresponse();
                    score=score+1;
                    break;

                  case 1:
                    touchresponse();
                    score=score+1;
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
          else if (time>=1500){
            time=0;
            score=0;
          }
          break;
        }
      }
      hardgame(score, GetGame);
    }
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

// Replay

void Replay(int GetGame){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Want to Replay?");
  lcd.setCursor(0,1);
  lcd.print("Click A to Replay");
  lcd.setCursor(0,2);
  lcd.print("Click * to Reset");
  char key = kpd.getKey();
  if(key !=NO_KEY)  // Check for a valid key.
  {
    switch (key){
    case 'A':
      {
        SameGame(GetGame);
        break;
      }
    case '*':
      {
        Game();
        break;
      }
    }
  }
  delay(400);
}

// Getting the Game

int GetGame(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Which Game Mode?");
  lcd.setCursor(0,1);
  lcd.print("A for FreePlay");
  lcd.setCursor(0,2);
  lcd.print("B for Guided Game");
  char keyG = kpd.getKey();
  if(keyG !=NO_KEY)  // Check for a valid key.
  {
    switch (keyG){
    case 'A':
      {
        int game=1;
        return game;
        break;
      }
    case 'B':
      {
        lcd.setCursor(0,0);
        lcd.print("Which Level?");
        lcd.setCursor(0,1);
        lcd.print("A for Easy");
        lcd.setCursor(0,2);
        lcd.print("B for Medium");
        lcd.setCursor(0,3);
        lcd.print("C for Hard");
        char keyG2 = kpd.getKey();
        if(keyG2 !=NO_KEY)  // Check for a valid key.
        {
          switch (keyG2){
          case 'A':
            {
              int game=2;
              return game;
              break;
            }
          case 'B':
            {
              int game=3;
              return game;
              break;
            }
          case 'C':
            {
              int game=4;
              return game;
              break;
            }
          }
        }
      }
    }
  }
}

// Game

 void Game()
 {
  int game = GetGame();
  Ready();
  PlayGame(game);
  Replay(game);
 }
 
// SameGame 
 
 void SameGame(int GetGame)
 {
  Ready();
  PlayGame(GetGame);
  Replay(GetGame);
 }
 
// Ready

void Ready()
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Ready to Start?");
   lcd.setCursor(0,1);
   lcd.print("Click A to Continue");
   lcd.setCursor(0,1);
   lcd.print("Click * to Reset");
   char key = kpd.getKey();
   if(key !=NO_KEY)  // Check for a valid key.
  {
    switch (key){
    case 'A':
      {
        break;
      }
    case '*':
      {
        Game();
        break;
      }
    }
  }
  delay(400);
}
   

// Playing the Game

void PlayGame(int game){
  switch (game){
  case 1:
    Freeplay();
    break;

  case 2:
    easygame(0, game);
    break;

  case 3:
    medgame(0, game);
    break;

  case 4:
    hardgame(0, game);
    break;
  }
}

// touch response

void touchresponse(){
  digitalWrite(touchre, HIGH);
  delay(3000);
  digitalWrite(touchre, LOW);
}

// button response

void buttonresponse(){
  digitalWrite(buttonre, HIGH);
  delay(3000);
  digitalWrite(buttonre, LOW);
}

// push response

void pushresponse(){
  digitalWrite(pushre, HIGH);
  delay(3000);
  digitalWrite(pushre, LOW);
}

// joystick response

void joystickresponse(){
  digitalWrite(joystickre, HIGH);
  delay(3000);
  digitalWrite(joystickre, LOW);
}

// spin response

void spinresponse(){
  digitalWrite(spinre, HIGH);
  delay(3000);
  digitalWrite(spinre, LOW);
}

// pull response

void pullresponse(){
  digitalWrite(pullre, HIGH);
  delay(3000);
  digitalWrite(pullre, LOW);
}
