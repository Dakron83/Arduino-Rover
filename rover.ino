#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *flMotor = AFMS.getMotor(3);
Adafruit_DCMotor *frMotor = AFMS.getMotor(4);
Adafruit_DCMotor *rlMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rrMotor = AFMS.getMotor(2);


int lSpeed = 250;
int rSpeed = 179;
int btsignal = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Rover test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz


frMotor->setSpeed(0);
flMotor->setSpeed(0);
rrMotor->setSpeed(0);
rlMotor->setSpeed(0);
frMotor->run(RELEASE);
flMotor->run(RELEASE);
rrMotor->run(RELEASE);
rlMotor->run(RELEASE);

}

void loop() {
  // put your main code here, to run repeatedly:
  //this is our repeating loop - that will go round and round until we switch the Arduino off
  frMotor->setSpeed(rSpeed);
  flMotor->setSpeed(lSpeed);
  rrMotor->setSpeed(rSpeed);
  rlMotor->setSpeed(lSpeed);
    
       
//check if anything on the serial interface
//using the Arduino's default serial interface (pins 0 and 1)so no need to define these
    if (Serial.available() > 0) {
    // read the incoming serial:
    btsignal = Serial.read();
    }

  // if there is something on the serial interface it is read and assigned to btsignal
  // then a SWITCH (case) statement evaluates the bluetooth sent data via btsignal

  switch(btsignal)
  {
      case 'S':
        // stop all motors
        frMotor->run(RELEASE);
        flMotor->run(RELEASE);
        rrMotor->run(RELEASE);
        rlMotor->run(RELEASE);
        Serial.println("Stop\n"); //display message for test purposes when connected to a serial monitor
         btsignal='*';
        break;
      case 'F':
        //forward
        frMotor->run(FORWARD);
        flMotor->run(FORWARD);
        rrMotor->run(FORWARD);
        rlMotor->run(FORWARD);
        break;
      case 'L':
        //left
        frMotor->run(FORWARD);
        flMotor->run(BACKWARD);
        rrMotor->run(FORWARD);
        rlMotor->run(BACKWARD);
        break;
      case 'R':
        //right
        frMotor->run(BACKWARD);
        flMotor->run(FORWARD);
        rrMotor->run(BACKWARD);
        rlMotor->run(FORWARD);
        break;
      case 'B':
        //backward
        frMotor->run(BACKWARD);
        flMotor->run(BACKWARD);
        rrMotor->run(BACKWARD);
        rlMotor->run(BACKWARD);
        break;
      default:
        //stop
        frMotor->run(RELEASE);
        flMotor->run(RELEASE);
        rrMotor->run(RELEASE);
        rlMotor->run(RELEASE);
        break;
  }
  
}
