#include <avr/interrupt.h>
#include <imu.h>

/*
Ziel dieser Aufgabe ist die weitere Abstraktion der Motoransteuerung unter
Einbeziehung einer Geschwindigkeits und Entfernungsregelung. Dazu ist die
Implementierung einer Interruptbasierten Auswertung der Odometrie notwendig.

Die Odometrie ist auf den interruptfähigen digitalen Pins 15 und 19 angeschlossenen.
Konfigurieren Sie mithilfe der avr/interrupt.h die beiden Datenpins so, dass diese
bei jedem Flankenwechsel einen Interrupt auslösen. Mit deren Hilfe die Odometrie-Ticks
der beiden Räder gezählt werden können. Beachten Sie hierbei die unterschiedliche
Konfigurationen von PCINT9 und INT 2 (wie sie auch in der Vorlesung vorgestellt wurden).
Erweitern sie Ihren Code so, dass dieser auf vorhandene Motoren-Klassen und/oder
Funktionen zugreift und einen Regler implementiert. Der von Ihnen gewählte
Regelungsmechanismus soll auf Basis der Odometrie-Ticks unterschiedliche
Geschwindigkeitsprofile der Motoren kompensieren.

Darauf aufbauen soll eine Wegstreckenregelung umgesetzt werden, die Distanzen
in cm oder Winkel in Grad entgegen nimmt und diese Strecke dann möglichst genau
abfährt. Am Ende soll der Roboter drive(50) cm auf dem Tisch zurücklegen,
sich um rotate(180)° drehen und wieder drive(50) cm fahren, sodass dieser
wieder zum Ausgangspunkt zurückkommt. Es bleibt den Teams überlassen, ob die
Messung der Rotation über die Odometrie oder/und den Gyro umgesetzt wird.
 */

// D6 PWM (OC4A), D7 PWM (OC4B)
// D11 PWM (OC1A), D12 PWM (OC1B)


#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>

/*
 * Clock PC2
 * Data PC3
 * Latch PC4
 */
#define CLOCK_DELAY_MS 1

int x = 0;
int dez = 0;
boolean neg = false;
double xangle = 0;
double yangle = 0;
String inputString = "";
boolean stringComplete = false;
String commandList[10];

byte EngIn[4] = {0, 0, 0, 0};

int m_targetAddress;

//for interrupt handling
volatile int engLeftTic = 0;
volatile int engRightTic = 0;
volatile int setpoint, measured_value, prev_error = 0, integral, lastTime, error, derivative, output, Kp = 17, Ki = 2, Kd = 10;
int stage = 0;

boolean distanceCompl = false;

void waitms(double timer) {
  double newtimer;
  newtimer = millis() + newtimer;
  while (millis() < newtimer);
}

// Distance Variablen
uint16_t adcval;
uint32_t valSUM;
int distance;
//Konstanten für Sensorauswahl
const int SEN_GP2D12047 = 0;
const int SEN_2Y0A2121 = 1;


int mode = 3;
int dir;

// IMU Variablne
double IMU_Offset;  //Speichert den IMU_Offset
double IMU_Heading = 0;
double IMU_Heading_Target = 0;//90/36*50;
unsigned long IMU_IntTimer = 0;

double delta;

void setup() {
  Display_Init();

  //PA0 und PA1 als input
  //DDRA = 0x00;

  ADC_Init();

  Serial.begin(57600);
  _delay_ms(500);
  Serial.println("ADC Test");
  Serial.println("Begin Wire");

  Wire.begin();

  InitEngines();

  // Clear the 'sleep' bit to start the sensor.
  Serial.println("Clear the 'sleep' bit to start the sensor.");
  MPU9150_writeSensor(MPU9150_PWR_MGMT_1, 0);

  Serial.println("Setup compass");
  MPU9150_setupCompass();

  Serial.print("Get Offset = ");
  IMU_Offset = IMU_getOffset();
  Serial.println(IMU_Offset);

  Serial.println("Setup COMPLETE");

  updateOCR();

  inputString.reserve(200);

  textOut();
}

void loop()
{
  if (Serial.available()) {
    String inputString = Serial.readString();
    if (inputString.compareTo("42")==0){
      mode = 0;
      //IMU_Heading_Target = input;
    }
    else{
      mode = 4;
    }
    Serial.print("Drehe von aktuell ");
    Serial.print(IMU_Heading);
    Serial.print(" auf neu: ");
    Serial.println(IMU_Heading_Target);
  }

  IMU_calcHeading();

  switch (mode) {
    case 1:
      //Aufgabe 2: Entfernungsmesser
      distance = getDistance2(SEN_GP2D12047, 0);

      if (distance < 400 || distance > 4000) out(888); //Fehlerausgabe wenn kleiner als
      else out(distance);  //Ausgabe ans Display
      break;

    case 2:
      //Aufgabe 2: Wasserwaage
      //getIMUangle();
      Serial.print("x-Angle: ");
      Serial.print(xangle);
      Serial.print("  y-Angle: ");
      Serial.println(yangle);
      WaageOut();
      break;

    case 3:
      //Aufgabe 3: Winkel anfahren (Meggie)
      out(IMU_Heading * 100);
      /*
      Serial.print("Heading: ");
      Serial.print(IMU_Heading);
      Serial.print(" - Delta: ");
      Serial.println(delta);*/

      delta = IMU_Heading_Target - IMU_Heading;

      if (delta > 10) EngTurn(1, 154);
      else if (delta < -10) EngTurn(0, 154);
      else if (delta > 3) EngTurn(1, 145);
      else if (delta < -3) EngTurn(0, 145);
      else EngStopp();

      break;

    case 4:
      manipulateString(inputString);
      for(int i=0;i<10;i++){
        if(commandList[i]!=""){
          commandExecute(commandList[i]);
        }
      }

    break;
    default:
      // Aufgabe 3a: Kollisionsfrei fahren (Meggie)
      distance = getDistance2(SEN_GP2D12047, 0);
      //distance *= 10;

      out(distance);  //Ausgabe ans Display
      //Serial.println(distance);


      // Fahrverhalten
      if (distance < 400 || distance > 4000) EngForward(150);
      else if (distance < 1300) {
        EngForward(-160);
      }
      else if (distance < 1700) {
        EngTurn(0, 160);
      }
      else {
        EngForward(160);
      }

      break;
  }
}
