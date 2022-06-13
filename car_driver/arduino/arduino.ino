#define HEADER 'H'

const int MOVE_FORWARD[2] = {0, 2}; // 2 == -1 == up
const int MOVE_LEFT[2] = {2, 0};    // move left
const int MOVE_RIGHT[2] = {1, 0};   // move right
const int MOVE_BACK[2] = {0, 1};    // move back
const int MOVE_STOP[2] = {0, 0};    // stop

void setup() {
  Serial.begin(9600);
  Serial.println("initialized");
  Serial.setTimeout(10);
  begin();
}

void loop() {
  if (Serial.available() > 0) {
    String string = Serial.readString();
    string.trim();
    char header = string[0];
    if (header == HEADER) {
      int delimiter = string.indexOf(',');
      int x = string.substring(1, delimiter).toInt();
      int y = string.substring(delimiter + 1).toInt();
      processCommand(x, y);
    }
  }
}

#define DEADZONE 1
// @param cmd the thing that tells it what to do, usually a vector(01, 22).
void processCommand(const int x, const int y) {
  if (x > 100 || x < -100 || y > 100 || y < -100) {
    Serial.println("invalid command");
  }
  if (x < DEADZONE && x >= 0) {
    // apply brakes to motora
    brakeMotorA();
  } else if (x < 0) {
    motorABackward(abs(x) + 155);
  } else {
    // positive number: 100 + 155 = 255
    motorAForward(x + 155);
  }
  if (y < DEADZONE && y >= 0) {
    // apply brakes to motorb
    brakeMotorB();
  } else if (y < 0) { // negative number: -100 + 355 = 255
    motorBBackward(abs(y) + 155);
  } else {
    // apply speed to motorb
    motorBForward(y + 155);
  }
  Serial.print("x: ");
  Serial.print(String(x));
  Serial.print(" y: ");
  Serial.println(String(y));
}