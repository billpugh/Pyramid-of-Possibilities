/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(513, 1);


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test! v2");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(25);  // 10 rpm   
}

void loop() {
  int chunk = 513;
  digitalWrite(13, HIGH);
  Serial.println("Single coil steps");
  myMotor->step(chunk, FORWARD, SINGLE); 
  myMotor->step(chunk, BACKWARD, SINGLE); 

digitalWrite(13, LOW);
  Serial.println("Double coil steps");
  myMotor->step(chunk, FORWARD, DOUBLE); 
  myMotor->step(chunk, BACKWARD, DOUBLE);

  digitalWrite(13, HIGH);
  Serial.println("Interleave coil steps");
  myMotor->step(chunk, FORWARD, INTERLEAVE); 
  myMotor->step(chunk, BACKWARD, INTERLEAVE); 

  digitalWrite(13, LOW);
  Serial.println("Microstep steps");
  myMotor->step(chunk, FORWARD, MICROSTEP); 
  myMotor->step(chunk, BACKWARD, MICROSTEP);
}
