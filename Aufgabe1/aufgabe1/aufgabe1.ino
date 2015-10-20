/*
 * Praktische Aufgabe 1:
 * Auf dem Display soll ein Zählwerk sichbar werden, dass im Zahlenbereich 
 * von -199 bis 999 arbeitet. Kommazahlen sind entsprechend zu integrieren. 
 * Ob der Wechsel zwischen Auf- und Abzählen über einen Tastendruck 
 * gesteuert wird oder eine (Arduino-)Zeitfunktion dafür benutzt wird, 
 * bleibt Ihnen überlassen.
 */


int latchPin = 33;
int clockPin = 35;
int dataPin = 34;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for(int x=0; x<23; x++){
    out(x);
   delay(1000);
  }
 
}

void out(int o){
  digitalWrite(dataPin, HIGH);
  Clock();
  for(int i=0; i<34; i++){
    /*if(i == o)
      digitalWrite(dataPin, HIGH);
    else
      digitalWrite(dataPin, LOW);*/
    Clock();
  }
}

void Clock(){
  digitalWrite(clockPin,HIGH);
  delay(1);
  digitalWrite(clockPin,LOW);
  delay(1);
}
