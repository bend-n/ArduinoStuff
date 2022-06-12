#include <AFMotor.h>  // adafruit motor shield library
#include "RobotMotor.h" 

void setup(){
    motorBegin(MOTOR_LEFT);
    motorBegin(MOTOR_RIGHT);
    motorSetSpeed(MOTOR_LEFT, 15);
    motorSetSpeed(MOTOR_RIGHT, 15);
    motorStop(MOTOR_LEFT);
    motorStop(MOTOR_RIGHT);
}

void loop(){}