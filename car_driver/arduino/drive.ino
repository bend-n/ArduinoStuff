#define MotorA 12 // left motor
#define BrakeMotorA 9
#define MotorASpeed 3

#define MotorB 13 // right motor
#define BrakeMotorB 8
#define MotorBSpeed 11

#define SPEED 255 // speed of motors

void begin() {
  // Setup Channel A
  pinMode(MotorA, OUTPUT);
  pinMode(BrakeMotorA, OUTPUT);

  // Setup Channel B
  pinMode(MotorB, OUTPUT);
  pinMode(BrakeMotorB, OUTPUT);
}

void motorAForward(int speed) {
  digitalWrite(MotorA, HIGH);      // forward
  digitalWrite(BrakeMotorA, LOW);  // brake off
  analogWrite(MotorASpeed, speed); // speed of motor
}

void motorBForward(int speed) {
  digitalWrite(MotorB, HIGH);      // forward
  digitalWrite(BrakeMotorB, LOW);  // brake off
  analogWrite(MotorBSpeed, speed); // speed of motor
}

void motorBBackward(int speed) {
  digitalWrite(MotorB, LOW);       // backwards
  digitalWrite(BrakeMotorB, LOW);  // brake off
  analogWrite(MotorBSpeed, speed); // speed of motor
}

void motorABackward(int speed) {
  digitalWrite(MotorA, LOW);       // backwards
  digitalWrite(BrakeMotorA, LOW);  // brake off
  analogWrite(MotorASpeed, speed); // speed of motor
}

void forward() {
  motorAForward(SPEED);
  motorBForward(SPEED);
}

void backward() {
  motorABackward(SPEED);
  motorBBackward(SPEED);
}

void brakeMotorA() {
  digitalWrite(brakeMotorA, HIGH); // engage brake
  analogWrite(MotorASpeed, 0);     // slow
}

void brakeMotorB() {
  digitalWrite(brakeMotorB, HIGH); // engage brake
  analogWrite(MotorBSpeed, 0);     // slow
}

void stop() {
  brakeMotorA();
  brakeMotorB();
}

void left() {
  brakeMotorA();
  motorBForward(SPEED);
}

void right() {
  brakeMotorB();
  motorAForward(SPEED);
}