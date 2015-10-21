/*
 * Praktische Aufgabe 1:
 * Auf dem Display soll ein Zählwerk sichbar werden, dass im Zahlenbereich
 * von -199 bis 999 arbeitet. Kommazahlen sind entsprechend zu integrieren.
 * Ob der Wechsel zwischen Auf- und Abzählen über einen Tastendruck
 * gesteuert wird oder eine (Arduino-)Zeitfunktion dafür benutzt wird,
 * bleibt Ihnen überlassen.
 */

#include <avr/io.h>
#include <util/delay.h>

/*
 * Clock PC2
 * Data PC3
 * Latch PC4
 */
#define CLOCK_DELAY_MS 1
int x = 0;

void out(int o) {
  //Startbit
  PORTC |= _BV(PORTC3);
  Clock();

  //Berechne die einzelnen Werte für Stellen 1-3
  int t = o;
  int d[3];
  for (int i = 2; i >= 0; i--) {
    d[i] = t % 10;
    t = t / 10;
  }

  for (int i = 0; i <= 2; i++) {
    //Gebe die Segmente der 3 Digits aus
    ShiftDigit( d[i] );
  }

  //Unbelegte Bits werden durchgeschaltet
  for (int i = 25; i < 36; i++) {
    Clock();
  }
}

//Erzeugt ein Clock-Cycle
void Clock(void) {
  _delay_ms(1);
  PORTC |= _BV(PORTC2);
  _delay_ms(1);
  PORTC &= ~_BV(PORTC2);
}

void ShiftDigit(int in) {
  //Laufe durch die 8 Segmente des Digits und schalte entsprechend den Ausgang
  for (int i = 7; i >= 0; i--) {
    byte dig = GetDigit(in);
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
    default: return 0b00000000;
  }
}

int main (void)
{
  /* set die drei Steuerleitungen als Output (in einem Befehl auch möglich?!)*/
  DDRC |= _BV(DDC2);  //CLK
  DDRC |= _BV(DDC3);  //Data
  DDRC |= _BV(DDC4);  //LATCH

  while (1) {
    out(x);
    _delay_ms(50);
    
    // Erhöhe Testausgabe o um 1
    x = (x + 1) % 1000;
  }
}




