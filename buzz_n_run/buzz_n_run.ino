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
int direction = 1;

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
    // check direction
    if (speed >= 90) {
        direction = 1; // forward
    } else {
        direction = -1; // backward
    }

    // check for incoming bytes
    if (Serial.available() > 0) {
        cmd = Serial.readStringUntil('\n');

    if (cmd == "buzz") {
        // turn on buzzer
        tone(buzz_pin, 784, 500); //E5
        delay(100);
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
        // turn off built-in LED
        digitalWrite(LED_BUILTIN, LOW);
    }

    if (cmd == "green_blink") {
        // turn on green LED
        digitalWrite(green_led_pin, HIGH);
        delay(200);
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

// stop
void stop()
{
    for (speed; speed != 90; speed -= direction) {
        left.write(speed);
        inv_speed = 180 - speed;
        right.write(inv_speed);
        delay(1);
    }
}

// backward
void backward()
{
    for (speed; speed >= 45; speed -= 1) {
        left.write(speed);
        inv_speed = 180 - speed;
        right.write(inv_speed);
        delay(1);
    }

    delay(200);

    /*
    for (speed = 45; speed != 90; speed -= direction) {
        left.write(speed);
        inv_speed = 180 - speed;
        right.write(inv_speed);
        delay(1);
    }
    */
}

// forward
void forward()
{
    for (speed; speed <= 135; speed += direction) {
        left.write(speed);
        inv_speed = 180 - speed;
        right.write(inv_speed);
        delay(1);
    }
    delay(200);
    /*
    for (speed = 135; speed != 90; speed -= direction) {
        left.write(speed);
        inv_speed = 180 - speed;
        right.write(inv_speed);
        delay(1);
    }
    */
}

// left turn
void turn_left()
{
    for (speed; speed >= 45; speed -= 1) {
        left.write(speed);
        right.write(speed);
        delay(1);
    }
    delay(500);
    for (speed = 45; speed < 90 ; speed += 1) {
        left.write(speed);
        right.write(speed);
        delay(1);
    }
}

// right turn
void turn_right()
{
    for (speed; speed <= 135; speed += 1) {
        left.write(speed);
        right.write(speed);
        delay(1);
    }
    delay(500);
    for (speed = 135; speed > 90 ; speed -= 1) {
        left.write(speed);
        right.write(speed);
        delay(1);
    }
}

