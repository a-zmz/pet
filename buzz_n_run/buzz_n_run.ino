/*
this makes serial control of builtin LED of arduino board, buzzer, and motors
*/

// include servo library
#include <Servo.h>
// create servo objects
Servo left, right;

/*
define global variables
*/
// digital green LED pin
int green_led_pin = 12;
// digital buzzer pin
int buzz_pin = 11;
// left servo pin
int left_servo = 8;
// right servo pin
int right_servo = 9;

// speed
int speed = 90;
int inv_speed = 180 - speed;
// direction
int direction = 90 - speed;

// initiate cmd as string
String cmd = "";

void setup() {
    // setup serial port
    Serial.begin(19200);

    // initialise digital pin builtin_led as an output
    pinMode(LED_BUILTIN, OUTPUT);
    // initialise digital green LED pin as an output
    pinMode(green_led_pin, OUTPUT);
    // initialise digital buzzer pin as an output
    pinMode(buzz_pin, OUTPUT);

    // attach servo pins
    left.attach(left_servo);
    right.attach(right_servo);

    // initialise servos
    left.write(speed);
    right.write(inv_speed);

}

void loop() {
    // check for incoming bytes
    if (Serial.available() > 0) {
        cmd = Serial.readStringUntil('\n');

    if (cmd == "buzz") {
        // turn on buzzer
        tone(buzz_pin, 659, 500); //E5
        delay(500);
        tone(buzz_pin, 523, 250); //C5
        delay(250);
    }

    if (cmd == "no_buzz") {
        // turn off buzzer
        digitalWrite(buzz_pin, LOW);
    }

    if (cmd == "red_on") {
        // turn on built-in LED
        digitalWrite(LED_BUILTIN, HIGH);
    }

    if (cmd == "red_off") {
        // turn on built-in LED
        digitalWrite(LED_BUILTIN, LOW);
    }

    if (cmd == "green_on") {
        // turn on green LED
        digitalWrite(green_led_pin, HIGH);
    }

    if (cmd == "green_off") {
        // turn off green LED
        digitalWrite(green_led_pin, LOW);
    }

    if (cmd == "forward") {
        // move forward
        forward();
    }

    if (cmd == "backward") {
        // move backward
        backward();
    }

    if (cmd == "stop") {
        // stop
        stop();
    }

    if (cmd == "turn_left") {
        // turn_left
        turn_left();
    }

    if (cmd == "turn_right") {
        // turn_right
        turn_right();
    }
    delay(10);
    }
}

/*
motors gradually increase to half-max speed
*/

// forward
void forward()
{
    for (speed = 90; speed >= 45; speed -= 1) {
        left.write(speed);
        inv_speed = 180 - speed;
        right.write(inv_speed);
        delay(1);
    }
}

// backward
void backward()
{
    for (speed = 90; speed <= 135; speed += 1) {
        left.write(speed);
        inv_speed = 180 - speed;
        right.write(inv_speed);
        delay(1);
    }
}

// stop
void stop()
{
    for (speed; speed = 90; speed += direction * 5/abs(direction)) {
        left.write(speed);
        inv_speed = 180 - speed;
        right.write(inv_speed);
        delay(1);
    }
}

// left turn
void turn_left()
{
    for (speed; speed = 135; speed += direction/abs(direction)) {
        left.write(speed);
        right.write(speed);
        delay(1);
    }
}

// right turn
void turn_right()
{
    for (speed = 90; speed = 45; speed += direction/abs(direction)) {
        left.write(speed);
        right.write(speed);
        delay(1);
    }
}
