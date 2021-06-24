///imports///
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <AccelStepper.h>

int Tea1switchPin = 2;
int Tea2switchPin = 24;
int Tea3switchPin = 26;
int val1;    
int val2;   
int val3;   
int craneSwitchPin = 31;  ///switch is connected to pin 19 (interrupt compatible pin)
int craneSwitchPinValue;
int wagonSwitchPin = 29;  ///switch is connected to pin 19 (interrupt compatible pin)
int wagonSwitchPinValue;
int WagonHomePosition;
int WagonDestination = 0;
int pos=0;
///INIT STEPPER///
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
///INIT SERVOS///
Servo shovel_servo;  
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *craneStepper = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *wagonStepper = AFMS.getStepper(200, 1);

void craneForwardStep() {  
  craneStepper->onestep(FORWARD, SINGLE);
}
void craneBackwardStep() {  
  craneStepper->onestep(BACKWARD, SINGLE);
}

void wagonForwardStep() {  
  wagonStepper->onestep(FORWARD, SINGLE);
}
void wagonBackwardStep() {  
  wagonStepper->onestep(BACKWARD, SINGLE);
}

AccelStepper AccelCranestepper(craneForwardStep, craneBackwardStep); // use functions to step
AccelStepper AccelWagonstepper(wagonForwardStep, wagonBackwardStep); // use functions to step



void setup() {
  Serial.begin(9600);
  Serial.println("Teararium turned ON");
  setupMenu();
  Serial.println("Menu OK");
  //set tea switches as inputs
  pinMode(Tea1switchPin, INPUT);
  pinMode(Tea2switchPin, INPUT);
  pinMode(Tea3switchPin, INPUT);
  pinMode(craneSwitchPin, INPUT);    // Set the switch pin as input
  ///Crane setup///
  Serial.println("K");
  AFMS.begin(1600);
  Serial.println("hhhK");
  ///Servos setup///

//  attachInterrupt (digitalPinToInterrupt (craneSwitchPin), craneSwitchPressed, CHANGE);
Serial.println("jojo");
  initialize_teararium();
}

void loop() {
  val1 = digitalRead(Tea1switchPin);
  val2 = digitalRead(Tea2switchPin);
  val3 = digitalRead(Tea3switchPin);
  if (val1 == HIGH) { 
     prepare_tea(1);
  }

  
  displayMenu();
}

void initialize_teararium(){
  initialize_crane();
  initialize_wagon();
  displace_wagon(3);
  displace_wagon(4);
  activate_shovel();
  displace_wagon(0);

  
}
