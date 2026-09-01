#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
const int trigPin = 13;
const int echoPin = 12;
const int S0 = A2;
const int S1 = A1;
const int S2 = A4;
const int S3 = A3;
const int OE = A0;
const int sensorOut = A5;
const int In1 = 7;
const int In2 = 13;
const int In3 = 12;
const int In4 = 4;
const int EnA = 6;
const int EnB = 5;


void setup() {
  // put your setup code here, to run once:
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){1, 2, 3, 9}, SensorCount);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(OE, LOW);
  Serial.begin(9600);
}

void loop() {
  
  // Colour Sensor
  colourCheck();
  // Line Sensor Array
  qtr.read(sensorValues);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();
  // Motors
  leftGo();
  rightGo();
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void colourCheck()
{
  // red reading
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int redFrequency = pulseIn(sensorOut, LOW);
  // green reading
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int greenFrequency = pulseIn(sensorOut, LOW);
  // blue reading
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int blueFrequency = pulseIn(sensorOut, LOW);
  // output
  Serial.print("r - ");
  Serial.print(redFrequency);
  Serial.print("   ");
  Serial.print("g - ");
  Serial.print(greenFrequency);
  Serial.print("   ");
  Serial.print("b - ");
  Serial.print(blueFrequency);
  Serial.print("   ");
}

void leftGo()
{
  analogWrite(EnA, 255);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
}

void leftStop()
{
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
}

void rightGo()
{
  analogWrite(EnA, 255);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void rightStop()
{
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
