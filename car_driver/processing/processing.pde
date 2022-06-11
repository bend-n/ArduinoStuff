import processing.serial.*;

private static char STOP = 'v';
private static char HEADER = 'H';

char current = STOP;

Serial port;

void setup() {
    frameRate(5);
    printArray(Serial.list());
    port = new Serial(this, Serial.list()[0], 9600);
}


void draw() {} // Empty draw() needed to keep the program running

void keyPressed() {
    updateKeys(key, true);
}

void keyReleased() {
    updateKeys(key, false);
}

boolean isValidKey(char key) {
    return key == 'a' || key == 'w' || key == 's' || key == 'd';
}

void write(char key) {
    char data[] = {HEADER, key};
    String towrite = new String(data);
    println(towrite);
    port.write(towrite);
}

void updateKeys(char key, boolean on) {
    if (isValidKey(key)) {
        if (!on || key != current) {
            current = on ? key : STOP;
            write(current);
        }
    }
}
