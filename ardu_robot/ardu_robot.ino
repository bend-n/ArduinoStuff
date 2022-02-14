/**********************************************************
MyRobot.ino

Initial sketch structured using tabs

Michael Margolis 4 July 2012
***********************************************************/

#include <AFMotor.h>  // adafruit motor shield library
#include "RobotMotor.h"    // 2wd or 4wd motor library

#include "globalDefines.h"  // global defines

// Setup runs at startup and is used configure pins and init system variables
void setup()
{
  Serial.begin(9600);
  blinkNumber(8); // open port while flashing. Needed for Leonardo only    
  
  motorBegin(MOTOR_LEFT); 
  motorBegin(MOTOR_RIGHT); 
 
  irSensorBegin();    // initialize sensors 
  pinMode(LED_PIN, OUTPUT); // enable the LED pin for output

  Serial.println("Waiting for a sensor to detect blocked reflection");
}

void loop()
{
   // call a function when reflection blocked on left side
   if(lookForObstacle(OBST_LEFT_EDGE) == true)   {   
     calibrateRotationRate(DIR_LEFT,360);  // calibrate ccw rotation
   }
   // as above for right sensor
   if(lookForObstacle(OBST_RIGHT_EDGE) == true)   {   
     calibrateRotationRate(DIR_RIGHT, 360);  // calibrate CW rotation
   }  
}

// function to indicate numbers by flashing the built-in LED
void blinkNumber( byte number) {
   pinMode(LED_PIN, OUTPUT); // enable the LED pin for output
   while(number--) {
     digitalWrite(LED_PIN, HIGH); delay(100);
     digitalWrite(LED_PIN, LOW);  delay(400);
   }
}

/**********************
 code to look for obstacles
**********************/

// returns true if the given obstacle is detected
boolean lookForObstacle(int obstacle)
{
  switch(obstacle) {
     case  OBST_FRONT_EDGE: return irEdgeDetect(DIR_LEFT) ||
                                   irEdgeDetect(DIR_RIGHT); 
     case  OBST_LEFT_EDGE:  return irEdgeDetect(DIR_LEFT); 
     case  OBST_RIGHT_EDGE: return irEdgeDetect(DIR_RIGHT);      
  } 
  return false; 
}

/*************************************
 functions to rotate the robot
*************************************/
  
// return the time in milliseconds to turn the given angle at the given speed
long rotationAngleToTime( int angle, int speed)
{
int fullRotationTime; // time to rotate 360 degrees at given speed

  if(speed < MIN_SPEED)
    return 0; // ignore speeds slower then the first table entry
  
  angle = abs(angle);
  
  if(speed >= 100)
    fullRotationTime = rotationTime[NBR_SPEEDS-1]; // the last entry is 100%
  else
 { 
    int index = (speed - MIN_SPEED) / SPEED_TABLE_INTERVAL ; // index into speed and time tables
    int t0 =  rotationTime[index];
    int t1 = rotationTime[index+1];    // time of the next higher speed 
    fullRotationTime = map(speed,  speedTable[index],  speedTable[index+1], t0, t1);  
   // Serial.print("index= ");  Serial.print(index); Serial.print(", t0 = ");  Serial.print(t0);  Serial.print(", t1 = ");  Serial.print(t1); 
 }
 // Serial.print(" full rotation time = ");  Serial.println(fullRotationTime);
  long result = map(angle, 0,360, 0, fullRotationTime);
  return result; 
}

// rotate the robot from MIN_SPEED to 100% increasing by SPEED_TABLE_INTERVAL
void calibrateRotationRate(int sensor, int angle)
{  
  Serial.print(locationString[sensor]);
  Serial.println(" calibration" );    
  for(int speed = MIN_SPEED; speed <= 100; speed += SPEED_TABLE_INTERVAL)
  {
    delay(1000);
    blinkNumber(speed/10);   
 
    if( sensor == DIR_LEFT)
    {    // rotate left
      motorReverse(MOTOR_LEFT,  speed); 
      motorForward(MOTOR_RIGHT, speed);  
    }
    else if( sensor == DIR_RIGHT)
    {    // rotate right
      motorForward(MOTOR_LEFT,  speed);
      motorReverse(MOTOR_RIGHT, speed);
    }
    else
       Serial.println("Invalid sensor");     
       
    int time = rotationAngleToTime(angle, speed);

    Serial.print(locationString[sensor]);
    Serial.print(": rotate ");
    Serial.print(angle);
    Serial.print(" degrees at speed ");
    Serial.print(speed);
    Serial.print(" for ");
    Serial.print(time);
    Serial.println("ms");
    delay(time); 
    motorStop(MOTOR_LEFT);
    motorStop(MOTOR_RIGHT);  
    delay(2000); // two second delay between speeds
  }    
}

