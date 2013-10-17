int actiond()
{
  int actd;
  while(0!=1) {
  int timed=millis();
  digitalWrite(outpin,HIGH);
  int vald=digitalRead(inpin);
  if (vald>= HIGH) {
  digitalWrite(outpin, LOW);
    actd=1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Yay");
    delay(3000);
    break;
  }
  else if (timed >= 15000){
  digitalWrite(outpin, LOW);
    actd=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Aww");
    delay(3000);
    break;
  }
  }
  return actd;
}
