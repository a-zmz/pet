/*
this makes builtin LED of arduino board blinks depending on voltage controlled
by potentiometer values
*/

//#include "helper.ino"
//#include "play_imperialmarch.ino"

// define global variables
int alg_lsens_pin = 0; // analogue light sensor pin num
int green_led_pin = 12; // digital green LED pin num
int buzz_pin = 11; // digital buzzer pin num

void setup() {
    // initialise digital pin builtin_led as an output
    pinMode(LED_BUILTIN, OUTPUT);
    // initialise digital green LED pin as an output
    pinMode(green_led_pin, OUTPUT);
    // initialise digital buzzer pin as an output
    pinMode(buzz_pin, OUTPUT);

    // setup serial port
    Serial.begin(9600);
}

void loop() {
    // read analog input from lightsensor
    int alg_lsens_vol = analogRead(alg_lsens_pin);
    Serial.println(alg_lsens_vol); // print out light sensor voltage

    if (alg_lsens_vol > 300) {
        // turn on buzzer
        /*
        playIM(buzz_pin);
        */
        digitalWrite(buzz_pin, HIGH); // voltage high, turn buzzer on
        digitalWrite(buzz_pin, LOW); // voltage low, turn buzzer off
        tone(buzz_pin, 659, 500); //E5
        delay(500);
        tone(buzz_pin, 659, 500);
        delay(500);
        tone(buzz_pin, 659, 500);
        delay(500);
        tone(buzz_pin, 523, 250); //C5
        delay(250);
        tone(buzz_pin, 523, 250);
        delay(250);
        tone(buzz_pin, 659, 500); //E5
        delay(500);
        tone(buzz_pin, 659, 500);
        delay(500);
        tone(buzz_pin, 659, 500);
        delay(500);
        tone(buzz_pin, 523, 350);
        delay(250);
        tone(buzz_pin, 784, 200); //G5
        delay(200);
        tone(buzz_pin, 659, 500);
        delay(500);
        tone(buzz_pin, 523, 350); //C5
        delay(250);
        tone(buzz_pin, 784, 200); //G5
        delay(200);
        tone(buzz_pin, 659, 1000);
        delay(500);

        tone(buzz_pin, 988, 500); //B5
        delay(500);
        tone(buzz_pin, 988, 500);
        delay(500);
        tone(buzz_pin, 988, 500);
        delay(500);
        tone(buzz_pin, 1047, 500); //C6
        delay(500);
        tone(buzz_pin, 784, 200); //G5
        delay(200);
        tone(buzz_pin, 622, 500); //Eb5
        delay(500);
        tone(buzz_pin, 523, 500); //C5
        delay(500);
        tone(buzz_pin, 784, 200); //G5
        delay(200);
        tone(buzz_pin, 659, 1000); //E5
        delay(500);

        tone(buzz_pin, 2637, 500); //E7
        delay(500);
        tone(buzz_pin, 659, 500); //E5
        delay(350);
        tone(buzz_pin, 659, 350); //E5
        delay(350);
        tone(buzz_pin, 2637, 500); //E7
        delay(500);
        tone(buzz_pin, 622, 500); //Eb
        delay(500);
        tone(buzz_pin, 587, 200); //D5
        delay(100);
        tone(buzz_pin, 554, 200); //Db5
        delay(100);
        tone(buzz_pin, 523, 200); //C5
        delay(100);
        tone(buzz_pin, 554, 200); //Db5
        delay(300);
        tone(buzz_pin, 698, 200); //F5
        delay(100);
        tone(buzz_pin, 988, 500); //B5
        delay(500);
        tone(buzz_pin, 880, 500); //A5
        delay(500);
        tone(buzz_pin, 831, 200); //Ab5
        delay(100);
        tone(buzz_pin, 784, 200); //G5
        delay(100);
        tone(buzz_pin, 698, 200); //F5
        delay(100);
        tone(buzz_pin, 784, 200); //G5
        delay(500);
        tone(buzz_pin, 523, 200); //C5
        delay(100);

        // blink LEDs
        digitalWrite(LED_BUILTIN, HIGH); // voltage high, turn red LED on
        digitalWrite(green_led_pin, LOW); // voltage low, turn green LED off
        delay(alg_lsens_vol); // wait in ms

        digitalWrite(LED_BUILTIN, LOW); // voltage low, turn red LED off
        digitalWrite(green_led_pin, HIGH); // voltage high, turn green LED on
        delay(alg_lsens_vol); // wait in ms
    } else {
        digitalWrite(buzz_pin, LOW); // voltage high, turn buzzer on
        digitalWrite(green_led_pin, LOW); // voltage low, turn green LED off
        digitalWrite(LED_BUILTIN, LOW); // voltage low, turn red LED off
    }

}
