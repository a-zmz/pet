/*
React to audio input
*/

// includes the "servo" library
#include <Servo.h>
// creates two servo objects, one for each motor
Servo left, right;

// left servo pin
int left_servo = 8;
// right servo pin
int right_servo = 9;

void setup() {
    // Initialize serial port
    Serial.begin(19200);

    // init LED pin
    pinMode(LED_BUILTIN, OUTPUT);
    // Attach servo pins
    right.attach(left_servo);
    left.attach(right_servo);

    // Initialize (no motion)
    left.write(90);
    right.write(90);

}

void loop() {
  
    // Check for any incoming bytes
    if (Serial.available() > 0) {
        char newChar = Serial.read();
        //String command = Serial.readStringUntil("\n"); //this line cannot be here

        // turn LED on
        if (newChar == 'o') {
        //if (command.equalsIgnoreCase("on")) {
              digitalWrite(LED_BUILTIN, HIGH);
        }

        // turn LED off
        if (newChar == 'd') {
        //if (command.equalsIgnoreCase("off")) {
              digitalWrite(LED_BUILTIN, LOW);
        }

        // Respond to command "f"
        if (newChar == 'f') {
        //if (command.equalsIgnoreCase("f")) {
              forward();
        }

        // Respond to command "b"
        if (newChar == 'b') {
        //if (command.equalsIgnoreCase("b")) {
              backward();
        }

        // Respond to command "l"
        if (newChar == 'l') {
        //if (command.equalsIgnoreCase("l")) {
              turn_left();
        }

        // Respond to command "r"
        if (newChar == 'r') {
        //if (command.equalsIgnoreCase("r")) {
              turn_right();
        }

        // Respond to command "x"
        if (newChar == 'x') {
        //if (command.equalsIgnoreCase("x")) {
              stop();
        }

        // Wait a bit
        delay(10);
    }

    // Wait a bit
    delay(1);
}

// Forward
void forward()
{
  left.write(45);
  right.write(135);
}

// Backward
void backward()
{
  left.write(135);
  right.write(45);
}

// Left
void turn_left()
{
  left.write(45);
  right.write(45);
}

// Right
void turn_right()
{
  left.write(135);
  right.write(135);
}

// Stop
void stop()
{
  left.write(90);
  right.write(90);
}
