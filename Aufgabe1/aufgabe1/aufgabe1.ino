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

void out(int x) {
  //Startbit
  PORTC |= _BV(PORTC3);
  Clock();
  for (int i = 1; i < 35; i++) {
    if(x != i)
      PORTC &= ~_BV(PORTC3);
    else
      PORTC |= _BV(PORTC3);
    Clock();
  }
  //36er Clock - Wird ausgegeben!
  Clock();
}

//Erzeugt ein Clock-Cycle
void Clock(void) {
  PORTC |= _BV(PORTC2);
  _delay_ms(CLOCK_DELAY_MS);
  PORTC &= ~_BV(PORTC2);
  _delay_ms(CLOCK_DELAY_MS);
}

//Gibt die Segmentbelegung für jedes Digit zurück
byte Digit(int in){
  switch(in){
    case 0: return 0b11111100;
    case 1: return 0b01100000;
    case 2: return 0b11011010;
    case 3: return 0b11110010;
    case 4: return 0b01100110;
    case 5: return 0b10110110;
    case 6: return 0b10111110;
    case 7: return 0b11100000;
    case 8: return 0b11111110;
    case 9: return 0b11011010;
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
    for (int x = 0; x <= 24; x++) {
      out(x);
      _delay_ms( 250);
    }
  }
}




