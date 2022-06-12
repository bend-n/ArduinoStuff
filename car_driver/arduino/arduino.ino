#define HEADER 'H'

#define TOTAL_BYTES 3 // hmmm

const int MOVE_FORWARD[2] = {0, 2}; // 2 == -1 == up
const int MOVE_LEFT[2] = {2, 0};    // move left
const int MOVE_RIGHT[2] = {1, 0};   // move right
const int MOVE_BACK[2] = {0, 1};    // move back
const int MOVE_STOP[2] = {0, 0};    // stop

void setup() {
  Serial.begin(9600);
  Serial.println("initialized");
  begin();
}

void loop() {
  if (Serial.available() >= TOTAL_BYTES) {
    // sample format: H11 or H02, etc.
    char header = Serial.read();
    if (header == HEADER) { // done reading header, next number is a tag
      char tmp = Serial.read();
      int x = (tmp - '0');
      tmp = Serial.read();
      int y = (tmp - '0');
      Serial.println(y, BIN);
      Serial.println(x, BIN);
      Serial.println("this is what I recived boss");
      if (is_tag_valid(x, y)) {
        processCommand(x, y); // process the command
      } else {
        Serial.print(x, BIN);
        Serial.print(y, BIN);
        Serial.println(": unknown tag");
      }
    } else {
      Serial.print("unknown header: ");
      Serial.println(header);
    }
  }
}

bool is_tag_valid(const int x, const int y) {
  return x > 0 && x < 3 && y > 0 && y < 3;
}

// @param cmd the thing that tells it what to do, usually a vector(01, 22).
void processCommand(const int x, const int y) {
  const int cmd[] = {x, y};
  if (cmd == MOVE_FORWARD) {
    forward();
  } else if (arrayCmp(cmd, MOVE_STOP)) {
    stop();
  } else if (arrayCmp(cmd, MOVE_LEFT)) {
    left();
  } else if (arrayCmp(cmd, MOVE_RIGHT)) {
    right();
  } else if (arrayCmp(cmd, MOVE_BACK)) {
    backward();
  } else {
    Serial.print('[');
    Serial.print(x);
    Serial.print(cmd[0]);
    Serial.print(cmd[1]);
    Serial.print(y);
    Serial.println("] Ignored");
  }
}

bool arrayCmp(const int array[], const int array2[]) {
  return array[0] == array2[0] && array[1] == array2[1];
}