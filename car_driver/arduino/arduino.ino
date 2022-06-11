#define HEADER 'H'

#define TOTAL_BYTES 2 // hmmm
#define number_of_keys 5

enum { MOV_LEFT, MOV_RIGHT, MOV_FORWARD, MOV_BACK, MOV_ROTATE, MOV_STOP };

const char tags[] = {'w', 'a', 's', 'd', 'v'};
const char *states[] = {"Left", "Right", "Forward", "Back", "Rotate", "Stop"};
const int DIR_LEFT = 0;
const int DIR_RIGHT = 1;
const int DIR_CENTER = 2;

const char *locationString[] = {"Left", "Right", "Center"}; // labels for debug

const int LED_PIN = 13;

int commandState = MOV_STOP; // what robot is told to do

const char MOVE_FORWARD = 'w'; // move forward
const char MOVE_LEFT = 'a';    // move left
const char MOVE_RIGHT = 'd';   // move right
const char MOVE_BACK = 's';    // move back
const char STOP = 'v';         // stop

void setup() {
  Serial.begin(9600);
  Serial.println("initialized");
  begin();
}

void loop() {
  if (Serial.available() >= TOTAL_BYTES) {
    // sample format: Hv or Hd, etc.
    char header = Serial.read();
    if (header == HEADER) {     // done reading header, next letter is a tag
      char tag = Serial.read(); // read the first tag
      if (is_tag_valid(tag) == true) {
        Serial.write(tag);
        Serial.println(" recieved");
        processCommand(tag); // process the command
      } else {
        Serial.write(tag);
        Serial.println(": unknown tag");
      }
    } else {
      Serial.print("unknown header: ");
      Serial.println(header);
    }
  }
}

bool is_tag_valid(char tag) {
  for (int i = 0; i < number_of_keys; i++) {
    Serial.print(tags[i]);
    if (tag == tags[i]) {
      return true;
    }
  }
  return false;
}

void changeCmdState(int newState) {
  if (newState != commandState) {
    Serial.print("cc");
    Serial.print(states[commandState]);
    Serial.print("->");
    Serial.println(states[newState]);
    commandState = newState;
  }
}

void processCommand(char cmd) {
  switch (cmd) {
  case STOP: {
    changeCmdState(MOV_STOP);
    stop();
    break;
  }
  case MOVE_LEFT: {
    changeCmdState(MOV_ROTATE);
    left();
    break;
  }
  case MOVE_RIGHT: {
    changeCmdState(MOV_ROTATE);
    right();
    break;
  }
  case MOVE_FORWARD: {
    changeCmdState(MOV_FORWARD);
    forward();
  } break;
  case MOVE_BACK: { // s is hard without 40 buttons
    changeCmdState(MOV_BACK);
    backward();
    break;
  }
  default:
    Serial.print('[');
    Serial.write(cmd);
    Serial.println("] Ignored");
    break;
  }
}