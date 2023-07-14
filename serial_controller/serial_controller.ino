/*
Serial Controller
- Respond to single character commands received via serial with servo motion
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

    // Respond to command "f"
    if(newChar == 'f') {
      forward();
    }

    // Respond to command "b"
    if(newChar == 'b') {
      backward();
    }

    // Respond to command "l"
    if(newChar == 'l') {
      turn_left();
    }

    // Respond to command "r"
    if(newChar == 'r') {
      turn_right();
    }

    // Respond to command "x"
    if(newChar == 'x') {
      stop();
    }
  }

  // Wait a bit
  delay(1);
}

// Forward
void forward()
{
  left.write(0);
  right.write(180);
}

// Backward
void backward()
{
  left.write(180);
  right.write(0);
}

// Left
void turn_left()
{
  left.write(0);
  right.write(0);
}

// Right
void turn_right()
{
  left.write(180);
  right.write(180);
}

// Stop
void stop()
{
  left.write(90);
  right.write(90);
}
