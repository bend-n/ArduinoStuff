
// defines to identify sensors
const int SENSE_IR_LEFT  = 0;
const int SENSE_IR_RIGHT = 1;

// defines for directions
const int DIR_LEFT   = 0;
const int DIR_RIGHT  = 1;
const int DIR_CENTER = 2;
    
const char* locationString[] = {"Left", "Right",   "Center"}; // Debug labels
// http://arduino.cc/en/Reference/String for more on character string arrays

// obstacles constants 
const int OBST_NONE       = 0;  // no obstacle detected
const int OBST_LEFT_EDGE  = 1;  // left edge detected 
const int OBST_RIGHT_EDGE = 2;  // right edge detected
const int OBST_FRONT_EDGE = 3;  // edge detect at both left and right sensors

const int LED_PIN = 13;

/**** End of Global Defines ****************/

