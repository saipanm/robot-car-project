#include <ESP8266WiFi.h>

// Define motor direction control pins
#define LEFTF1 D6   // Replacing D1 with D6
#define LEFTF2 D7   // Replacing D2 with D7
#define RIGHTF1 D8  // Replacing D5 with D8
#define RIGHTF2 D0  // Replacing D6 with D0

// Define PWM speed control pins
#define SPEED_A D3
#define SPEED_B D4

String inputString = "";       // Stores incoming serial data
bool stringComplete = false;   // Flag for checking if the message is complete
const int fixedSpeed = 307; 

unsigned long moveStartTime = 0;  // To track the start time of the movement
const unsigned long moveDuration = 100;  // Movement duration (500 ms)
bool isMovingForward = false;    // Flags for direction control
bool isMovingReverse = false;
bool isMovingLeft = false;
bool isMovingRight = false;

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    inputString.reserve(200);

    // Initialize motor direction control pins as output
    pinMode(LEFTF1, OUTPUT);
    pinMode(LEFTF2, OUTPUT);
    pinMode(RIGHTF1, OUTPUT);
    pinMode(RIGHTF2, OUTPUT);
    
    // Set initial motor direction states to LOW
    digitalWrite(LEFTF1, LOW);
    digitalWrite(LEFTF2, LOW);
    digitalWrite(RIGHTF1, LOW);
    digitalWrite(RIGHTF2, LOW);

    // Set PWM pins for speed control
    pinMode(SPEED_A, OUTPUT);
    pinMode(SPEED_B, OUTPUT);
    
    // Set PWM speed to 50% duty cycle for both motors
    analogWrite(SPEED_A, fixedSpeed);
    analogWrite(SPEED_B, fixedSpeed);
}

void loop() {
    
    // Read serial input manually
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        inputString += inChar;
        if (inChar == '\n') {
            stringComplete = true;
        }
    }

    if (stringComplete) {
        inputString.trim();
        String command = splitString(inputString, 0);
        stringComplete = false;

        // Process the command
        if (command == "forward") {
            startForward();
            Serial.println("Moving Forward");
        } else if (command == "reverse") {
            reverse();
            Serial.println("Reversing");
        } else if (command == "stop") {
            stop();
            Serial.println("Stopping");
        } else if (command == "left") {
            moveLeft();
            Serial.println("Turning Left");
        } else if (command == "right") {
            moveRight();
            Serial.println("Turning Right");
        } else {
            Serial.println("Error: Unrecognized command");
        }
        inputString = "";  // Clear input after processing
    }

    // Check movement timeout with reduced duration
    if (isMovingForward && (millis() - moveStartTime >= moveDuration)) {
        stop();
        Serial.println("Timeout: Stopping Forward Movement");
    }
    if (isMovingReverse && (millis() - moveStartTime >= moveDuration)) {
        stop();
        Serial.println("Timeout: Stopping Reverse Movement");
    }
    if (isMovingLeft && (millis() - moveStartTime >= moveDuration)) {
        stop();
        Serial.println("Timeout: Stopping Left Turn");
    }
    if (isMovingRight && (millis() - moveStartTime >= moveDuration)) {
        stop();
        Serial.println("Timeout: Stopping Right Turn");
    }
}

// Function to split a string based on commas
String splitString(String data, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == ',' || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// Forward motion
void startForward() {
    digitalWrite(LEFTF1, HIGH);
    digitalWrite(LEFTF2, LOW);
    digitalWrite(RIGHTF1, HIGH);
    digitalWrite(RIGHTF2, LOW);
    moveStartTime = millis();
    isMovingForward = true;
    isMovingReverse = false;
}

// Reverse motion
void reverse() {
    digitalWrite(LEFTF1, LOW);
    digitalWrite(LEFTF2, HIGH);
    digitalWrite(RIGHTF1, LOW);
    digitalWrite(RIGHTF2, HIGH);
    moveStartTime = millis();
    isMovingReverse = true;
    isMovingForward = false;
    isMovingLeft = false;
    isMovingRight = false;
}

// Left turn
void moveLeft() {
    digitalWrite(LEFTF1, LOW);
    digitalWrite(LEFTF2, HIGH);
    digitalWrite(RIGHTF1, HIGH);
    digitalWrite(RIGHTF2, LOW);
    moveStartTime = millis();
    isMovingLeft = true;
    isMovingForward = false;
    isMovingReverse = false;
}

// Right turn
void moveRight() {
    digitalWrite(LEFTF1, HIGH);
    digitalWrite(LEFTF2, LOW);
    digitalWrite(RIGHTF1, LOW);
    digitalWrite(RIGHTF2, HIGH);
    moveStartTime = millis();
    isMovingRight = true;
    isMovingForward = false;
    isMovingReverse = false;
}

// Stop all motion
void stop() {
    digitalWrite(LEFTF1, LOW);
    digitalWrite(LEFTF2, LOW);
    digitalWrite(RIGHTF1, LOW);
    digitalWrite(RIGHTF2, LOW);
    isMovingForward = false;
    isMovingReverse = false;
    isMovingLeft = false;
    isMovingRight = false;
}
