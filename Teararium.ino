///imports///
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <AccelStepper.h>
#include "max6675.h"
#include <HX711_ADC.h> // https://github.com/olkal/HX711_ADC
#include <Wire.h>
    
int Tea1switchPin = 2;
//int Tea2switchPin = 24;
//int Tea3switchPin = 26;
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
int CraneHomePosition;
int CraneDestination = 0;
int arm_up_angle = 70;   
int arm_down_angle = 15; 
int closed_teaball_angle = 160; 
int open_teaball_angle = 0;
int pos=0;
///INIT STEPPER///
#include <TMCStepper.h>

#define EN_PIN_craneStepper           38 // Enable
#define DIR_PIN_craneStepper         58 // Direction
#define STEP_PIN_craneStepper         57 // Step
#define SERIAL_PORT_craneStepper Serial1 // TMC2208/TMC2224 HardwareSerial port

#define EN_PIN_wagonStepper           40 // Enable
#define DIR_PIN_wagonStepper         60 // Direction
#define STEP_PIN_wagonStepper         59 // Step
#define SERIAL_PORT_wagonStepper Serial1 // TMC2208/TMC2224 HardwareSerial port

#define R_SENSE 0.11f // Match to your driver
                     // SilentStepStick series use 0.11
                     // UltiMachine Einsy and Archim2 boards use 0.2
                     // Panucatt BSD2660 uses 0.1
                     // Watterott TMC5160 uses 0.075

TMC2208Stepper craneDriver = TMC2208Stepper(&SERIAL_PORT_craneStepper, R_SENSE); // Hardware Serial0
TMC2208Stepper wagonDriver = TMC2208Stepper(&SERIAL_PORT_wagonStepper, R_SENSE); // Hardware Serial0

constexpr uint32_t steps_per_mm = 80;

#include <AccelStepper.h>
AccelStepper craneStepper = AccelStepper(craneStepper.DRIVER, STEP_PIN_craneStepper, DIR_PIN_craneStepper);
AccelStepper wagonStepper = AccelStepper(wagonStepper.DRIVER, STEP_PIN_wagonStepper, DIR_PIN_wagonStepper);

// Create the motor shield object with its I2C address
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60); 
Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(0x61); 
Adafruit_MotorShield AFMS3 = Adafruit_MotorShield(0x60); 

///INIT SERVOS///
Servo shovel_servo;  
Servo arm_servo;
Servo teaball_servo;

//INIT Scale
HX711_ADC LoadCell(42, 44); //  pin 42 et 44 digital PWM
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_DCMotor *Silo3Motor = AFMS2.getMotor(1);
Adafruit_DCMotor *Silo2Motor = AFMS2.getMotor(3);
Adafruit_DCMotor *Silo1Motor = AFMS2.getMotor(4);
Adafruit_DCMotor *CraneMotor = AFMS2.getMotor(2);
Adafruit_DCMotor *PumpMotor = AFMS3.getMotor(1);
Adafruit_DCMotor *StirrerMotor = AFMS3.getMotor(2);


int PumpMotorState = 0;
int StirrerMotorState = 0;
//INIT CAPTEUR TEMPERATURE
//int thermoDO = 38;
//int thermoCS = 36;
//int thermoCLK = 34;
int thermoDO = 26;
int thermoCS = 24;
int thermoCLK = 22;
int desired_temp = 20;
MAX6675 thermocouple1(thermoCLK, thermoCS, thermoDO);
//thermocouple1.setOffset(-10);
//INIT RELAI
int ThermoblockRelayPin1 = 43;
int ThermoblockRelayPin2 = 45;
int solenoidRelayPin = 47;
//INIT FLOW SENSOR
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int L_per_hour; // Computed litres/hour
unsigned int mL_per_sec; // Computed mL/sec
unsigned char flowsensor = 18; //pin 18 is an interruptable pin, raises event to interrupt(5) : cf doc interrupt Arduino Mega 2560
int desired_volume; //mL
float pouring_time;
float volume_poured;
float step_volume_poured;
float flowrate;
//Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
//Crane inputs
float up_to_down_time;


void setup() {
  Serial.begin(9600);
  Serial.println("Teararium turned ON");
  setupMenu();
  Serial.println("Menu OK");
  //set tea switches as inputs
  pinMode(Tea1switchPin, INPUT);
//  pinMode(Tea2switchPin, INPUT);
//  pinMode(Tea3switchPin, INPUT);
  pinMode(craneSwitchPin, INPUT);    // Set the switch pin as input
  pinMode(TeaBallDownSwitchPin, INPUT);
  pinMode(TeaBallUpSwitchPin, INPUT);
  ///Crane setup///
  Serial.println("Initializing motor Feather 1");
//  AFMS.begin(1600);
  Serial.println("motor Feather 1 initialized");
  ///Servos setup///
  //SETUP RELAY
  pinMode(solenoidRelayPin, OUTPUT);
  digitalWrite(solenoidRelayPin, HIGH);
  pinMode(ThermoblockRelayPin1, OUTPUT);
  digitalWrite(ThermoblockRelayPin1, HIGH);
  pinMode(ThermoblockRelayPin2, OUTPUT);
  digitalWrite(ThermoblockRelayPin2, HIGH);
  //SETUP SCALE
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(-6000); // à calibrer !
  //SETUP FLOW SENSOR
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  attachInterrupt(5, flow, RISING); // Setup Interrupt // interrupt(5) corresponds to pin 18 raising event
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
  initialize_steppers();
  initialize_teararium();
}

void loop() {
  analogReference(EXTERNAL);
  val1 = digitalRead(Tea1switchPin);
//  val2 = digitalRead(Tea2switchPin);
//  val3 = digitalRead(Tea3switchPin);
  if (val1 == HIGH) { 
     prepare_tea(1);
  }

  
  displayMenu();
}

void initialize_teararium(){


//    heat_thermoblock();
//    prepare_tea(1);
//  arm_smooth_up();
//  delay(3000);
//  arm_smooth_down();
//    delay(5000);
//  arm_smooth_up();
//  delay(3000);
//    compute_weight();
   
//    close_teaball();
//  pour_water(150);


  initialize_crane();
//  initialize_wagon();
//  initialize_arm();
//  displace_wagon(3);

  
//  unload_tea(3);

//  displace_wagon(4);
  rotate_crane(2);
  delay(2000);
  rotate_crane(1);
//  delay(2000);
//  unsigned long StartTime = millis();
//  pull_teaball_down();
//  unsigned long CurrentTime = millis();
//  up_to_down_time = CurrentTime - StartTime;
//  Serial.print("Temps de descente : ");
//  Serial.println(up_to_down_time);
//  delay(1000);
//  open_teaball();
//  displace_wagon(4);
//  activate_shovel();
//  delay(2000);
//  displace_wagon(0);
//  close_teaball();
//  pull_teaball_up();
//  delay(2000);
//  rotate_crane(1);
//  immerge_teaball();
//  delay(2000);
//  pull_teaball_up();
//  rotate_crane(0);
//  pull_teaball_down();
//  delay(1000);
//  open_teaball();
//  delay(3000);
//  close_teaball();
  pull_teaball_up();




  
////  initialize_arm();
//  displace_wagon(3);
////  delay(1000);
//  run_motor1();
//  displace_wagon(4);
//  activate_shovel();
//  displace_wagon(0);
//  pull_teaball_up();
//  delay(2500);
//  pull_teaball_down();
//  delay(1500);
//  open_teaball();
//  delay(3000);
//  close_teaball();
//    stir();
//    stop_stirring();
  //  arm_smooth_up();
//  prepare_tea(1);


}
