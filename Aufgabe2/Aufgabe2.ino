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
//#include <util/math.h>
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

// Diese Beispiel zeigt die Anwendung des ADC eines ATmega169
// unter Verwendung der internen Referenzspannung von nominell 1,1V.
// Zur Anpassung an andere AVR und/oder andere Referenzspannungen
// siehe Erläuterungen in diesem Tutorial und im Datenblatt
 
/* ADC initialisieren */
void ADC_Init(void)
{
  // die Versorgungsspannung AVcc als Referenz wählen:
  ADMUX = (1<<REFS0);    
  // oder interne Referenzspannung als Referenz für den ADC wählen:
  // ADMUX = (1<<REFS1) | (1<<REFS0);
 
  // Bit ADFR ("free running") in ADCSRA steht beim Einschalten
  // schon auf 0, also single conversion
  ADCSRA = (1<<ADPS1) | (1<<ADPS0);     // Frequenzvorteiler
  ADCSRA |= (1<<ADEN);                  // ADC aktivieren
 
  /* nach Aktivieren des ADC wird ein "Dummy-Readout" empfohlen, man liest
     also einen Wert und verwirft diesen, um den ADC "warmlaufen zu lassen" */
 
  ADCSRA |= (1<<ADSC);                  // eine ADC-Wandlung 
  while (ADCSRA & (1<<ADSC) ) {         // auf Abschluss der Konvertierung warten
  }
  /* ADCW muss einmal gelesen werden, sonst wird Ergebnis der nächsten
     Wandlung nicht übernommen. */
  (void) ADCW;
}
 
/* ADC Einzelmessung */
uint16_t ADC_Read( uint8_t channel )
{
  // Kanal waehlen, ohne andere Bits zu beeinflußen
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
  while (ADCSRA & (1<<ADSC) ) {   // auf Abschluss der Konvertierung warten
  }
  return ADCW;                    // ADC auslesen und zurückgeben
}
 
/* ADC Mehrfachmessung mit Mittelwertbbildung */
/* beachte: Wertebereich der Summenvariablen */
uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples )
{
  uint32_t sum = 0;
 
  for (uint8_t i = 0; i < nsamples; ++i ) {
    sum += ADC_Read( channel );
  }
 
  return (uint16_t)( sum / nsamples );
}
 

int main( void )
{
  uint16_t adcval;
  uint32_t valSUM;
  int distance;
  //float val;

    /* set die drei Steuerleitungen als Output (in einem Befehl auch möglich?!)*/
  DDRC |= _BV(DDC2);  //CLK
  DDRC |= _BV(DDC3);  //Data
  DDRC |= _BV(DDC4);  //LATCH
  
  ADC_Init();
  
  Serial.begin(57600);
  _delay_ms(1000);
  Serial.println("ADC Test");
  
  while( 1 ) {
    valSUM = 0;
    for(int i=0; i<250; i++)
    {
      adcval = ADC_Read(0);  // Kanal 0
      valSUM += adcval;
    }
    valSUM = valSUM / 250;
    // mach was mit adcval
    Serial.println(valSUM);
    //Serial.println("= adcval");

    //−95×LN((schwarze Oberfläche '406,480814729724'−42,5)÷5)+445
    distance = -95 * log((valSUM - 42.5)/5)+445;
    distance *= 100;
    out(distance);
    //_delay_ms(1000);
    //adcval = ADC_Read_Avg(2, 4);  // Kanal 2, Mittelwert aus 4 Messungen
    // mach was mit adcval
  }
}




