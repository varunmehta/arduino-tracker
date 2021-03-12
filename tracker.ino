#include<AccelStepper.h>
#define HALFSTEP   8
#define MOTOR_PIN_1  8     // IN1 on the ULN2003 driver 1
#define MOTOR_PIN_2  9     // IN2 on the ULN2003 driver 1
#define MOTOR_PIN_3  5     // IN3 on the ULN2003 driver 1
#define MOTOR_PIN_4  6     // IN4 on the ULN2003 driver 1

AccelStepper stepper1(HALFSTEP, MOTOR_PIN_1, MOTOR_PIN_3, MOTOR_PIN_2, MOTOR_PIN_4);

const int SWITCH = 12;      // the number of the pushbutton pin
const int POWER_LED = 13;   // the number of the POWER_LED pin

unsigned long currentMillis = 0; // value of millis each loop
unsigned long previousMillis = 0; // last time the led was updated

const int blinkDuration = 100; // milliseconds
const int blinkInterval = 2500; // milliseconds


// Initialize Everything
void setup() {
  Serial.begin(9600);
  Serial.print("Setting up");

  stepper1.setMaxSpeed(261.41);
  stepper1.setAcceleration(50.0);
  stepper1.setSpeed(261.41);

  // Initialize the POWER_LED pin as an output
  pinMode(POWER_LED, OUTPUT);

  // Initialize the SWITCH pin as an input:
  pinMode(SWITCH, INPUT);
  digitalWrite(SWITCH, HIGH);
}

/**
   LED blinks for 1/10th of a second every 2.5 seconds.
*/
void blink_led() {

  if (digitalRead(POWER_LED) == LOW) {
    if (currentMillis - previousMillis >= blinkInterval) {
      digitalWrite(POWER_LED, HIGH);
      previousMillis += blinkInterval;
    }
  } else {
    if (currentMillis - previousMillis >= blinkDuration) {
      digitalWrite(POWER_LED, LOW);
      previousMillis += blinkDuration;
    }
  }
}

/**
    When switch is turned on, motor turns
*/
void turn_motor() {
  // read the state of the switch value:
  int switchState = digitalRead(SWITCH);
  Serial.print(switchState);
  if (switchState == LOW) {
    stepper1.runSpeed();
  } else {
    stepper1.stop();
  }
}

/**
   Main method
*/
void loop() {
  // capture the latest value of millis()
  currentMillis = millis();   
  
  blink_led();
  turn_motor();
}
