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

void out();
void out(){
  PORTC |= _BV(PORTC3);
  Clock();
  for(int i=0; i<34; i++){
    Clock();
  }
}

//Setzt Clock Pin auf High und wieder auf LOW
void Clock(void){
  PORTC |= _BV(PORTC2);
  _delay_ms(CLOCK_DELAY_MS);
  PORTC &= ~_BV(PORTC2);
  _delay_ms(CLOCK_DELAY_MS);
}

int main (void)
{
  /* set pin 5 of PORTB for output*/
  DDRC |= _BV(DDC2);  //CLK
  DDRC |= _BV(DDC3);  //Data
  DDRC |= _BV(DDC4);  //LATCH

Serial.begin(115200);
Serial.println("STARTING");
 
 while(1) {
  for(int x=0; x<23; x++){
    out();
    _delay_ms( 1000);
  }
 }
}




