void Display_Init() {
  /* setze die drei Steuerleitungen für das Display als Output (in einem Befehl auch möglich?!)*/
  DDRC |= _BV(DDC2);  //CLK
  DDRC |= _BV(DDC3);  //Data
  DDRC |= _BV(DDC4);  //LATCH
}

void out(int o) {
  //Startbit
  PORTC |= _BV(PORTC3);
  Clock();

  int t = o;

  //Setzt Negativ flag, falls Wert negativ ist
  if (o < 0) {
    neg = true;
    t *= -0.01;
    dez = 2;
  }
  else
  {
    neg = false;

    //Verschiebe Komma.
    if (t >= 10000) {
      t = t / 100;
      dez = 2;
    }
    else if (t >= 1000) {
      t = t / 10;
      dez = 1;
    }
    else {
      dez = 0;
    }
  }

  //Berechne die einzelnen Werte für Stellen 1-3
  int d[3];
  for (int i = 2; i >= 0; i--) {
    d[i] = t % 10;
    t = t / 10;
  }

  if (neg == true) {
    if (d[0] == 1) d[0] = -1;
    else d[0] = -10;
  }

  for (int i = 0; i <= 2; i++) {
    //Gebe die Segmente der 3 Digits aus
    if (i == dez)
    {
      ShiftDigit( d[i], true);
    }
    else
    {
      ShiftDigit( d[i], false);
    }
  }

  //Unbelegte Bits werden durchgeschaltet
  for (int i = 25; i < 36; i++) {
    Clock();
  }
}

//Erzeugt ein Clock-Cycle
void Clock(void) {
  _delay_ms(CLOCK_DELAY_MS);
  PORTC |= _BV(PORTC2);
  _delay_ms(CLOCK_DELAY_MS);
  PORTC &= ~_BV(PORTC2);
  _delay_ms(CLOCK_DELAY_MS);
}

void ShiftDigit(int in, boolean dezpoint) {
  //Laufe durch die 8 Segmente des Digits und schalte entsprechend den Ausgang
  for (int i = 7; i >= 0; i--) {
    byte dig = GetDigit(in);
    if (dezpoint == true) dig |= 1 ;
    //if (negpoint == true) dig |= 1 << 1 ;

    if (((dig >> i)  & 0x01) != 1)
      PORTC &= ~_BV(PORTC3);
    else
      PORTC |= _BV(PORTC3);
    Clock();
  }

}

//Gibt die Segmentbelegung für jedes Digit zurück
byte GetDigit(int in) {
  switch (in) {
    case 0: return 0b11111100;
    case 1: return 0b01100000;
    case 2: return 0b11011010;
    case 3: return 0b11110010;
    case 4: return 0b01100110;
    case 5: return 0b10110110;
    case 6: return 0b10111110;
    case 7: return 0b11100000;
    case 8: return 0b11111110;
    case 9: return 0b11110110;
    case -1: return 0b01100010;
    case -10: return 0b00000010;
    default: return 0b00000000;
  }
}
