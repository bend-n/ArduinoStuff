
#include <AFMotor.h>  // adafruit motor shield library
#include "RobotMotor.h"    // 2wd or 4wd motor library

#define HEADER 'H'

#define TOTAL_BYTES 8// hmmm
#define number_of_keys 4

enum        {MOV_LEFT, MOV_RIGHT, MOV_FORWARD, MOV_BACK, MOV_ROTATE, MOV_STOP};
const char tags[] = {'w', 'a', 's', 'd'};
const char* states[] = {"Left", "Right", "Forward", "Back", "Rotate", "Stop"};
const int DIR_LEFT   = 0;
const int DIR_RIGHT  = 1;
const int DIR_CENTER = 2;
    
const char* locationString[] = {"Left", "Right", "Center"}; // labels for debug

const int LED_PIN = 13;

int commandState = MOV_STOP;    // what robot is told to do


const char MOVE_FORWARD = 'w'; // move forward
const char MOVE_LEFT    = 'a'; // move left
const char MOVE_RIGHT   = 'd'; // move right 
// const char PIVOT_CCW    = '?'; // rotate 90 degrees CCW
// const char PIVOT_CW     = '?'; // rotate 90 degrees CW
// const char PIVOT        = '?'; // rotation angle (minus rotates CCW)

// not used in this example
// const char MOVE_SPEED        = '?'; 
// const char MOVE_SLOWER       = '?'; // reduce speed 
// const char MOVE_FASTER       = '?'; // increase speed 

void setup() {
  Serial.begin(9600);
  Serial.println("initialized");
  moveBegin();
  moveSetSpeed(MIN_SPEED + 40);
}

void loop() {
  if ( Serial.available() >= TOTAL_BYTES) {
    // sample format: Hw0a0s1d0
    if (Serial.read() == HEADER) {
      for(int i = 0; i <= number_of_keys * 2; i++) {
        char tag = Serial.read(); // read the first tag
        if (tags[i / 2] == tag){ // perhaps works
          char key = Serial.read();
          Serial.print(tag); Serial.print(": "); Serial.println(key); // debug
          processCommand(tags[i], key); 
        }
        else {
          Serial.write(tag);
          Serial.println( ": unknown tag");
        }
      }
    }
  }
    else {
      Serial.print("missing header: ");
      Serial.println(HEADER);
    }
  }
}

void changeCmdState(int newState)
{
  if(newState != commandState)
  {
    // Serial.print("Changing Cmd state from "); Serial.print( states[commandState]); // dont need this logged
    // Serial.print(" to "); Serial.println(states[newState]);
    commandState = newState;
  } 
}


void processCommand(int cmd, int pressed)
{
  moveStop();
  changeCmdState(MOV_STOP);
  // byte speed;
  //Serial.write(cmd); // uncomment to echo
  
  switch(cmd)
  { 
   case MOVE_LEFT    : {
    if(pressed == 1) {
    changeCmdState(MOV_ROTATE);    
    moveRotate(-10); 
    break; 
    }
  }
  case MOVE_RIGHT   : { 
    if(pressed == 1) {
    changeCmdState(MOV_ROTATE);   
    moveRotate(10);     
    break; 
    }
  }
  case MOVE_FORWARD : {if(pressed == 1) {changeCmdState(MOV_FORWARD); moveForward();   break;}}
  case 's' : { // s is complicated, cause im trying to do this without 40 buttons
    if (pressed == 1){ 
      if (commandState != MOV_STOP) {
        changeCmdState(MOV_STOP);
        moveStop();
        break;
      }
      else if (commandState == MOV_STOP) {
        changeCmdState(MOV_BACK);
        moveBackward();
        break;
      }
    }
   }
  
  //  case PIVOT_CCW    : changeCmdState(MOV_ROTATE);  moveRotate(-90); break;
  //  case PIVOT_CW     : changeCmdState(MOV_ROTATE);  moveRotate(90);  break;
//  case PIVOT        : changeCmdState(MOV_ROTATE);  moveRotate(val); break; 
//  case MOVE_SPEED   : speed = val;    moveSetSpeed(speed);         break;
//  case SLOWER       : moveSlower(speedIncrement);                  break;
//  case FASTER       : moveFaster(speedIncrement);                  break;
   case '\r' : case '\n': break; // ignore cr and lf
   default :  Serial.print('['); Serial.write(cmd); Serial.println("] Ignored");  break;
  }
}


