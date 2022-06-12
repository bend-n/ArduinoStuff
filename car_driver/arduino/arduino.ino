#define HEADER 'H'

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
  if (Serial.available() > 0) {
    String string = Serial.readString();
    string.trim();
    char header = string[0];
    if (header == HEADER) {
      int delimiter = string.indexOf(',');
      int x = string.substring(1, delimiter).toInt();
      int y = string.substring(delimiter + 1).toInt();
      processCommand(x, y);
    } else {
      Serial.println("wrong header: " + String(header));
    }
  }
}

#define DEADZONE 10
// @param cmd the thing that tells it what to do, usually a vector(01, 22).
void processCommand(const int x, const int y) {
  if (x > 200 || x < 0 || y > 200 || y < 0) {
    Serial.println("invalid command");
  }
  if (x < DEADZONE) {
    // apply brakes to motora
    brakeMotorA();
  } else if (x > 100) {
    motorABackward((x - 100) + 155);
  } else {
    // apply speed to motora
    motorAForward(x + 155);
  }
  if (y < DEADZONE) {
    // apply brakes to motorb
    brakeMotorB();
  } else if (y > 100) {
    motorBBackward((y - 100) + 155);
  } else {
    // apply speed to motorb
    motorBForward(y + 155);
  }
  Serial.print("x: ");
  Serial.print(String(x));
  Serial.print(" y: ");
  Serial.println(String(y));
}