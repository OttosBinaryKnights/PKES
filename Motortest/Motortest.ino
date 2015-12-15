byte EngIn[4] = {0,0,0,0};

#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>

#include <imu.h>

void setup() {
  Serial.begin(57600);
  _delay_ms(500);
  Serial.println("ADC Test");
  Serial.println("Begin Wire");
  
  InitEngines();
  // put your setup code here, to run once:
  /*for(int i= 0; i<4; i++){
    pinMode(IN[i], OUTPUT);
    digitalWrite(IN[i], LOW);
  }*/

}

void loop() {
  for(int o= 0; o<256; o=o+2){
    EngIn[0] = o;
    EngIn[2] = o;
    
    updateOCR();
    
    delay(100);
  }
}



