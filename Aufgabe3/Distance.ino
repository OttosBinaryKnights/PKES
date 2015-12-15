/* ADC initialisieren */
void ADC_Init(void)
{
  // Versorgungsspannung als Referenz
  ADMUX = (1<<REFS0);    
  // interne Referenz
  // ADMUX = (1<<REFS1) | (1<<REFS0);

  ADCSRA = (1<<ADPS1) | (1<<ADPS0);     // Frequenzvorteiler
  ADCSRA |= (1<<ADEN);                  // ADC aktivieren
 
  /* "Dummy-Readout" */
 
  ADCSRA |= (1<<ADSC);                  // eine ADC-Wandlung 
  while (ADCSRA & (1<<ADSC) ) {         // auf Abschluss der Konvertierung warten
  }
  (void) ADCW;
}
 
uint16_t ADC_Read( uint8_t channel )
{
  // Kanal waehlen, ohne andere Bits zu beeinflußen
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
  while (ADCSRA & (1<<ADSC) ) {   // auf Abschluss der Konvertierung warten
  }
  return ADCW;                    // ADC auslesen und zurückgeben
}

int calcGP2D12047(int val){
  // Umrechnung durchgeführ für GP2D12047
  //−95×LN((schwarze Oberfläche '406,480814729724'−42,5)÷5)+445
        int dist = -95 * log((val - 42.5)/5)+445;
        dist *= 10;
  return dist;
}

