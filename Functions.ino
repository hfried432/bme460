//buttons

int buttons()
{

  double adc_in = analogRead(0);

  double voltage_in = adc_in/1023*5;

  
  if (voltage_in > vSELECT) return btnNONE;
  if (voltage_in < vRIGHT) return btnRIGHT;
  if (voltage_in < vUP) return btnUP;
  if (voltage_in < vDOWN) return btnDOWN;
  if (voltage_in < vLEFT) return btnLEFT;
  if (voltage_in < vSELECT) return btnSELECT;
  return btnNONE;
};

// getMode

int getMode()
{ 
  int modenumber=1;

  
  while (0!=1) {
    
    int button = buttons();
    switch(button)
    {
      case btnNONE:
      {
        break;
      }
      case btnUP:
      {
        if (modenumber==1){
          modenumber=2;
          Display(modenumber);
          delay(400);
        }
        else if (modenumber==2){
          modenumber=1;
          Display(modenumber);
          delay(400);
        }
        break;
      }
        case btnDOWN:
        {
        if (modenumber==1){
          modenumber=2;
          Display(modenumber);
          delay(400);
        }
        else if (modenumber==2){
          modenumber=1;
          Display(modenumber);
          delay(400);
        }
        break;
       }
        case btnSELECT:
        {
          delay(400);
          return modenumber;
          break;
        }
    }
  }
}

// getLevel

int getLevel(int gamemode)
{
  Display(3);
  if (gamemode==1){
    int levelnumber=3;
    Display(levelnumber);
  }
  else if (gamemode==2){
    int levelnumber=4;
    
    while (0!=1) {
    
    int button = buttons();
    switch(button)
    {
      case btnNONE:
      {
        break;
      }
      case btnUP:
      {
        if (levelnumber==4){
          levelnumber=5;
          Display(levelnumber);
          delay(400);
        }
        else if (levelnumber==5){
          levelnumber=6;
          Display(levelnumber);
          delay(400);
        }
        else if (levelnumber==6){
          levelnumber=4;
          Display(levelnumber);
          delay(400);
        }
        break;
      }
        case btnDOWN:
      {
        if (levelnumber==6){
          levelnumber=5;
          Display(levelnumber);
          delay(400);
        }
        else if (levelnumber==4){
          levelnumber=6;
          Display(levelnumber);
          delay(400);
        }
        else if (levelnumber==5){
          levelnumber=4;
          Display(levelnumber);
          delay(400);
        }
        break;
      }
        case btnSELECT:
        {
          delay(400);
          return levelnumber;
          break;
        }
      }
    }
   }
  }
 
 // LCD Display Name
 
 void Display(int number){
   lcd.clear();
   
   switch (number) {
     
   case 1:  
     lcd.setCursor(0,0);
     lcd.print("Game Mode?");
     lcd.setCursor(0,1);
     lcd.print("FreePlay");
     break;
     
   case 2:
     lcd.setCursor(0,0);
     lcd.print("Game Mode?");
     lcd.setCursor(0,1);
     lcd.print("Guided Game");
     break;
     
    case 3:
     break;
     
    case 4: 
     lcd.setCursor(0,0);
     lcd.print("Level?");
     lcd.setCursor(0,1);
     lcd.print("Easy");
     break;
     
    case 5:
     lcd.setCursor(0,0);
     lcd.print("Level?");
     lcd.setCursor(0,1);
     lcd.print("Medium");
     break;
     
    case 6:
     lcd.setCursor(0,0);
     lcd.print("Level?");
     lcd.setCursor(0,1);
     lcd.print("Hard");
     break;
   }
 }
 
 // Ready to Start
 
 void Ready()
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Ready to Start");
   lcd.setCursor(0,1);
   lcd.print("Up to continue");
   int buttonup = buttons();
   
   while (0!=1){
     if (buttonup == btnUP){
       break;
     }
     delay(100);
     buttonup = buttons();
   }
   delay(400);
 }
 
 // Ready for Next Activity
 
 void NextActivity()
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Next Activity?");
   lcd.setCursor(0,1);
   lcd.print("Up=Yes Down=No");
   int buttonnext = buttons();
   
   while (0!=1){
     if (buttonnext == btnUP){
       break;
     }
     else if (buttonnext == btnDOWN){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Waiting");
       lcd.setCursor(0,1);
       lcd.print("10 seconds");
       delay(10000);
     }
     delay(100);
     buttonnext = buttons();
   }
   delay(400);
 }
 
 // Replay
 
 void Replay()
 {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Want to Replay?");
   lcd.setCursor(0,1);
   lcd.print("Up=Yes Down=No");
   int buttonre = buttons();
   
   while (0!=1){
     if (buttonre == btnUP){
       // gamefunction
       break;
     }
     else if (buttonre ==btnDOWN){
       break;
     }
     delay(100);
     buttonre = buttons();
   }
   delay(400);
 }
