/*******************************************************
    RobotMotor.cpp // Adafruit 4WD version
    low level motor driver for use with adafruit motor shield and 4WD robot

    Motor constants used are defined AFMotor.h

    Copyright Michael Margolis May 8 2012
********************************************************/

#include <Arduino.h>  
#include <AFMotor.h>  // adafruit motor shield library
#include "RobotMotor.h"

const int differential = 0; // % faster left motor turns compared to right  

// tables hold time in ms to rotate robot 360 degrees at various speeds 
// this enables conversion of rotation angle into timed motor movement 
// The speeds are percent of max speed
// Note: low cost motors do not have enough torque at low speeds so
// the robot will not move below this value 
// Interpolation is used to get a time for any speed from MIN_SPEED to 100%

const int MIN_SPEED = 60; // first table entry is 60% speed
const int SPEED_TABLE_INTERVAL = 10; // each table entry is 10% faster speed
const int NBR_SPEEDS =  1 + (100 - MIN_SPEED)/ SPEED_TABLE_INTERVAL;
 
int speedTable[NBR_SPEEDS]  =  {60,   70,   80,   90,  100}; // speeds  
int rotationTime[NBR_SPEEDS] = {5500, 3300, 2400, 2000, 1750}; // time

AF_DCMotor motors[] = {
    AF_DCMotor(4, MOTOR34_1KHZ), // left front is Motor #4 
    AF_DCMotor(3, MOTOR34_1KHZ), // right front is Motor #3
	AF_DCMotor(1, MOTOR12_1KHZ), // left rear is Motor #1
    AF_DCMotor(2, MOTOR12_1KHZ)  // right rear is Motor #2
	};

int  motorSpeed[2]  = {0,0}; // left and right motor speeds stored here (0-100%)

void motorBegin(int motor)
{
  motorStop(motor);  // stop the front motor
  motorStop(motor+2); // stop the rear motor
}

// speed range is 0 to 100 percent
void motorSetSpeed(int motor, int speed)
{
  if( motor == MOTOR_LEFT && speed > differential)
    speed -= differential;
  motorSpeed[motor] = speed;           // save the value
  int pwm = map(speed, 0,100, 0,255);  // scale to PWM range
   
  motors[motor].setSpeed(pwm) ;
  motors[motor+2].setSpeed(pwm) ;
}

void motorForward(int motor, int speed)
{
  motorSetSpeed(motor, speed);
  motors[motor].run(FORWARD); 
  motors[motor+2].run(FORWARD);   
}

void motorReverse(int motor, int speed)
{
  motorSetSpeed(motor, speed);
  motors[motor].run(BACKWARD); 
  motors[motor+2].run(BACKWARD);   
}

void motorStop(int motor)
{
  // todo set speed to 0 ???
  motors[motor].run(RELEASE);      // stopped
  motors[motor+2].run(RELEASE);   
}

void motorBrake(int motor)
{
  motors[motor].run(BRAKE);      // stopped
  motors[motor+2].run(BRAKE); 
}