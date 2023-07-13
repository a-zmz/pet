/* this is the first run of mobo (?) */

/*
  NOTE
  Sending digital pulses was easy (even over a radio), but sending "analog" values
  was prone to noise and required more expensive transmitters/receivers.
  in arduino, a 1 ms pulse would be "0", a 1.5 ms pulse would be "90", and a 2 ms
  pulse would be "180".
  these servos control "speed":
  0 -- full speed clockwise
  90 -- stopped
  180 -- full speed counter-clockwise
*/

// includes the "servo" library
#include <Servo.h>

// creates servo objects, one for each motor
Servo left, right;

// set initial speed to 0
int speed = 0;
int left_pin = 8;
int right_pin = 9;

// Setup
void setup() {
  // Assign left servo to pin
  left.attach(left_pin);
  // Assign right servo to pin
  right.attach(right_pin);
}

void loop() {
  // move forward at constant half speed
  left.write(45); // clockwise 
  right.write(135); // counter-clockwise 
  delay(1500);
  left.write(90); // stop left servo
  right.write(90); // stop right servo
  delay(3000);

  // move backward at constant half speed
  left.write(135); // counter-clockwise
  right.write(45); // clockwise
  delay(1500);
  left.write(90); // stop left servo
  right.write(90); // stop right servo
  delay(3000);

  // run in circle at constant half speed, clockwise
  left.write(0); // clockwise 
  right.write(110); // counter-clockwise 
  delay(5000);
  left.write(90); // stop left servo
  right.write(90); // stop right servo
  delay(1500);

  // run in circle at constant half speed, clockwise
  left.write(180); // clockwise 
  right.write(80); // counter-clockwise 
  delay(5000);
  left.write(90); // stop left servo
  right.write(90); // stop right servo
  delay(1500);
}
