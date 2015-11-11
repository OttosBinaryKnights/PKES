/*
 * Praktische Aufgabe 2:
 * In dieser Aufgabe sollen die Grundlagen für eine erste Umgebungserfassung mithilfe von Infrarot-Distanz-Sensoren und der IMU (Inertial Measurement Unit) erfolgen. 
 * Ziel ist es dabei die Verarbeitungskette von Sensordaten kennenzulernen und zu implementieren:
 * Analog-Digital-Wandlung/Linearisierung
 * Erste Schritte mit der Inertialsensorik
 * Dabei sollen einerseits die an die Analogen-Pins angeschlossenen IR-Sensoren ausgelesen werden und deren (nicht-lineares) Messergebnis in einen Distanzwert umgerechnet werden. 
 * Es sollten mindestens die Distanzen zwischen 10cm und 25cm korrekt wiedergegeben werden (mehr ist auch nicht schlecht). Achten Sie genau den Sensor-Typen, da diese zwar gleich aussehen, 
 * aber sehr unterschiedliche Reichweiten und damit Kenngrößen haben. Auf jedem Sensor steht eine Bezeichnung des Typs.
 * Bei der Inertialsensorik soll zunächst nur der gemessene Beschleunigungswert in eine Orientierung (Winkellage gegenüber dem Horizont) übersetzt werden. Dies soll genutzt werden um eine einfache Wasserwage zu implementieren... Einfache trigonometrische Funktionen sind hier von Vorteil :-)
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
int dez = 0;
boolean neg = false;

//int ist in centi angegeben!
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

int main (void)
{
  /* set die drei Steuerleitungen als Output (in einem Befehl auch möglich?!)*/
  DDRC |= _BV(DDC2);  //CLK
  DDRC |= _BV(DDC3);  //Data
  DDRC |= _BV(DDC4);  //LATCH

  
//1. Set the MUX bit fields (MUX3:0) in ADC’s MUX register (ADMUX) equal to 0000 to select ADC Channel 0.
  //ADMUX &= 0b11110000;  //Kein Befehl eigentlich nötig ADC 0 standardmäßig selektiert
  
//2. Set the ADC Enable bit (ADEN) in ADC Control and Status Register A (ADCSRA) to enable the ADC module.
  ADCSRA |= _BV(ADEN);
  
//3. Set the ADC Pre-scalar bit fields (ADPS2:0) in ADCSRA equal to 100 to prescale the system clock by 16.
  ADPS |= 0b00000100;
  
//4. Set the Voltage Reference bit fields (REFS1:0) in ADMUX equal to 11 to select Internal 1.1V reference.
  //ADMUX |= (1 << REFS0); Ist schon 00
  
//5. Set the Start Conversion bit (ADSC) in ADCSRA to start a single conversion.
//6. Poll (wait) for the Interrupt Flag (ADIF) bit in the ADCSRA register to be set, indicating that a new conversion is completed.
//7. Once the conversion is over (ADIF bit becomes high) then read the ADC data
//register pair (ADCL/ADCH) to get the 10-bit ADC result value.

  Serial.begin(57600);
  _delay_ms(1000);
  Serial.println("Binary Knights - Aufgabe 1 v01");
  _delay_ms(1000);
  while (1) {
    Serial.println("STARTE TEST");
    Serial.println("Teste 0.00 bis 10.0");
    _delay_ms(1000);
    for (int x = 0; x <= 1000; x = x + 5)
    {
      out(x);
      _delay_ms(10);
      //Serial.println(x);
    }

    Serial.println("10 erreicht. Zaehle bis - 199");
    _delay_ms(1000);
    for (int x = 1000; x >= -19900; x = x - 100)
    {
      out(x);
      _delay_ms(20);
      //Serial.println(x);
    }

    Serial.println("-199 erreicht. Zaehle bis - 199");
    _delay_ms(1000);
    for (int x = -19900; x <= 99900; x = x + 100)
    {
      out(x);
      _delay_ms(20);
      //Serial.println(x);
    }

    Serial.println("Test fertig. Restart in 10 Sekunden ...");
    _delay_ms(10000);
  }
}




