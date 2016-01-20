
/*
 * MOTOREN
 * Laufen ab ca. 150 langsam an
 *
 *
*/
void InitEngines()
{
  DDRH |= ( 1 << 3 );
  DDRH |= ( 1 << 4 );
  DDRB |= ( 1 << 5 );
  DDRB |= ( 1 << 6 );

  ICR1   = 255; // Set top for timer 1
  //FastPWM non-inverting mode NO PRESCALING = 16 MHz
  TCCR1A = ( 1 << COM1A1 ) | ( 1 << COM1B1 ) | ( 1 << WGM11 );
  TCCR1B = ( 1 << WGM13  ) | ( 1 << WGM12 ) | ( 1 << CS10 );
  OCR1A  = 0; // Power FWD Left
  OCR1B  = 0; // Power RWD Left

  ICR4   = 255; // Set top for timer 4
  TCCR4A = ( 1 << COM1A1 ) | ( 1 << COM1B1 ) | ( 1 << WGM11 );
  TCCR4B = ( 1 << WGM13  ) | ( 1 << WGM12 ) | ( 1 << CS10 );
  OCR4A  = 0; // Power FWD Right
  OCR4B  = 0; // Power RWD Right

//interrupt init
  PORTD |= (1<<PD2);
  PORTJ |= (1<<PJ0);
  DDRD &= ~(0<<PD2);
  DDRJ &= ~(0<<PJ0);

//interruptmaskenregister
  EIMSK |= (1 << INT2);     // Enable external interrupt INT0
  EICRA |= (1 << ISC20);    // Trigger INT0 on falling edge

  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT9);

  ADC_Init();

}

ISR(INT2_vect){
  engRightTic+=1;
}

ISR(PCINT1_vect){
  engLeftTic+=1;
}

void EngStopp() {
  EngForward(0);
}

void EngForward(int speed) {
  setEngine(0, speed);
  setEngine(1, speed);
}

void Forward(int distance){
  int tics=getTic(distance);
  if(engLeftTic>tics){
    EngStopp();
    engLeftTic=0;
    engRightTic=0;
  } else {
    setEngine(0,150);
    setEngine(1,150+pidController());
  }

}

//dir 0= Links, 1= Rechts
void EngTurn(int dir, int speed) {
  if(dir<0) dir=0;
  setEngine(dir, speed*-1);
  setEngine(1 - dir, speed);
}

//if engineNum==0 -> right
//   engineNum==1 -> left
// speed -> value between 0 and 255


void setEngine(boolean engineNum, int speed) {
  /*Serial.print("setEngine ");
  Serial.print(engineNum);
  Serial.print(" = ");
  Serial.println(speed);*/

  if (speed < 0) {
    EngIn[0 + engineNum * 2] = 0;
    EngIn[1 + engineNum * 2] = -speed;
  }
  else
  {
    EngIn[0 + engineNum * 2] = speed;
    EngIn[1 + engineNum * 2] = 0;
  }
  updateOCR();
}

void updateOCR() {
  OCR1A  = EngIn[0];
  OCR1B  = EngIn[1];
  OCR4A  = EngIn[2];
  OCR4B  = EngIn[3];
/*
  for (int i = 0; i < 4; i++) {
    Serial.print(EngIn[i]);
    Serial.print("/");
  }
  Serial.println();*/
}

//dir 0= Links, 1= Rechts
boolean Turn(int dir, int angle){
  IMU_Heading_Target = angle;
  out(IMU_Heading * 100);

  delta = IMU_Heading_Target - IMU_Heading;

  if (delta > 10) EngTurn(dir, 154);
  else if (delta < -10) EngTurn(-dir, 154);
  else if (delta > 3) EngTurn(dir, 145);
  else if (delta < -3) EngTurn(-dir, 145);
  else {
    EngStopp();
    return true;
  }
  return false;
}

int getTic(int distance){
  return 36/16*distance;
}
