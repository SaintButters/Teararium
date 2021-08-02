///imports///
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <AccelStepper.h>
#include "max6675.h"

int Tea1switchPin = 2;
int Tea2switchPin = 24;
int Tea3switchPin = 26;
int val1;    
int val2;   
int val3;   
int craneSwitchPin = 31;  
int craneSwitchPinValue;
int wagonSwitchPin = 29;  
int wagonSwitchPinValue;
int TeaBallUpSwitchPin = 25;  
int TeaBallUpSwitchValue;
int TeaBallDownSwitchPin = 27;  
int TeaBallDownSwitchValue;
int WagonHomePosition;
int WagonDestination = 0;
int arm_up_angle = 70;   
int arm_down_angle = 15; 
int closed_teaball_angle = 160; 
int open_teaball_angle = 0;
int pos=0;
///INIT STEPPER///
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60); 
Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(0x61); 
Adafruit_MotorShield AFMS3 = Adafruit_MotorShield(0x63); 

///INIT SERVOS///
Servo shovel_servo;  
Servo arm_servo;
Servo teaball_servo;

// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *craneStepper = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *wagonStepper = AFMS.getStepper(200, 1);
Adafruit_DCMotor *SiloMotor1 = AFMS2.getMotor(1);
Adafruit_DCMotor *CraneMotor = AFMS2.getMotor(2);
Adafruit_DCMotor *PumpMotor = AFMS3.getMotor(1);

int PumpMotorState = 0;
//INIT CAPTEUR TEMPERATURE
int thermoDO = 38;
int thermoCS = 36;
int thermoCLK = 34;
int desired_temp = 20;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
//INIT RELAI
int resistorRelayPin1 = 43;
int resistorRelayPin2 = 45;
int solenoidRelayPin = 47;
//INIT FLOW SENSOR
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int L_per_hour; // Computed litres/hour
unsigned int mL_per_sec; // Computed mL/sec
unsigned char flowsensor = 33;
int desired_volume; //mL
float pouring_time;
float volume_poured;
float step_volume_poured;
float flowrate;
 // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;

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
  pinMode(TeaBallDownSwitchPin, INPUT);
  pinMode(TeaBallUpSwitchPin, INPUT);
  ///Crane setup///
  Serial.println("Initializing motor Feather 1");
  AFMS.begin(1600);
  Serial.println("motor Feather 1 initialized");
  ///Servos setup///
  //SETUP RELAY
  pinMode(solenoidRelayPin, OUTPUT);
  digitalWrite(solenoidRelayPin, HIGH);
    //SETUP FLOW SENSOR
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
//  attachInterrupt (digitalPinToInterrupt (craneSwitchPin), craneSwitchPressed, CHANGE);
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

//    prepare_tea(1);
//  arm_smooth_down(arm_up_angle, arm_down_angle);

  pull_teaball_up();
  delay(2500);
//  pull_teaball_down();
//  delay(1500);
//  open_teaball();
//  delay(3000);
//  close_teaball();
//  pour_water(150);
//  initialize_crane();
//  initialize_wagon();
//  initialize_arm();
//  displace_wagon(3);
//  delay(1000);
//  run_motor1();
//  displace_wagon(4);
//  activate_shovel();
//  displace_wagon(0);

  //  arm_smooth_up(arm_down_angle, arm_up_angle);


}
