#include <imu.h>

#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>

void setup() {
  /* set die drei Steuerleitungen als Output (in einem Befehl auch möglich?!)*/
  DDRC |= _BV(DDC2);  //CLK
  DDRC |= _BV(DDC3);  //Data
  DDRC |= _BV(DDC4);  //LATCH

  //PA0 und PA1 als input
  //DDRA = 0x00; 
  
  ADC_Init();
  
  Serial.begin(57600);
  _delay_ms(500);
  Serial.println("ADC Test");
  Serial.println("Begin Wire");

  Wire.begin();
  
  // Clear the 'sleep' bit to start the sensor.
  Serial.println("Clear the 'sleep' bit to start the sensor.");
  MPU9150_writeSensor(MPU9150_PWR_MGMT_1, 0);

  Serial.println("Setup compass");
  MPU9150_setupCompass(); 

  Serial.println("Setup COMPLETE");
}

void loop() {
  // put your main code here, to run repeatedly:

  int gz= MPU9150_readSensor(MPU9150_GYRO_ZOUT_L, MPU9150_GYRO_ZOUT_H);
  Serial.println(gz);
  
  _delay_ms(100);
}

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
