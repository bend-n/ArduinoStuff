#include <NewPing.h>

// Ultrasonic Sensor testing code. Written by a 13 year old.
//#include NewPing.h// Imports the NewPing Library.
#define ledPin 12
#define trigPin 10
#define echoPin 9
int duration, distance; // Add types 'duration' and 'distance'.

void setup()
{
  Serial.begin(9600);
  pinMode (ledPin, OUTPUT); // The LED must be controlled by Arduino, it means it is an output type.
  pinMode (trigPin, OUTPUT);// Same as above, the TRIG pin will send the ultrasonic wave.
  pinMode (echoPin, INPUT); // The ECHO pin will recieve the rebounded wave, so it must be an input type.
}
void loop()
{
  digitalWrite (ledPin, LOW); // Here, LOW means off and HIGH means on.
  digitalWrite (trigPin, HIGH);
  delay(50);
  digitalWrite (trigPin, LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=(duration/2)/29.1;

  if(distance <=30) 
  {
    digitalWrite (ledPin, HIGH);
    delay(50);
  }

  else
  {
    digitalWrite (ledPin, LOW);
    delay(50);
    Serial.print("cm");
    Serial.println(distance);
  }
}