void WaageOut() {
  //Startbit
  PORTC |= _BV(PORTC3);
  Clock();
  
  //Laufe durch die 8 Segmente des Digits und schalte entsprechend den Ausgang
  for (int in=0; in<3; in++){
    for (int i = 7; i >= 0; i--) {
      byte dig = GetWaageDigit(in);
      if (((dig >> i)  & 0x01) != 1)
        PORTC &= ~_BV(PORTC3);
      else
        PORTC |= _BV(PORTC3);
      Clock();
    }
  }

  //Unbelegte Bits werden durchgeschaltet
  for (int i = 25; i < 36; i++) {
    Clock();
  }
}

byte GetWaageDigit(int digit){
  byte output = 0b00000000;

  //if (abs(xangle)<5) output = output || 0b01101100;  //centered

  //Vertikale abweichung
  if(xangle<-10)
  {
    output = 0b10000000;
  }
  else if(xangle>10){
    output = 0b00010000;
  }
  else{
    output = 0b00000010;
  }
  if(yangle<-30 && digit == 0) output |= 0b00001100;
  else if(yangle<-15 && digit == 0) output |= 0b01100000;
  
  if(yangle>30 && digit == 2) output |= 0b01100000;
  else if(yangle>15 && digit == 2) output |= 0b00001100;

  if(abs(yangle)<=15 && digit == 1){
    if(yangle>-5) output |= 0b01100000;
    if(yangle<5) output |= 0b00001100;
  }
  

  //Fehler
  if(abs(xangle)>40 || abs(yangle)>40 ) return 0b11111111;
  return output;
}
