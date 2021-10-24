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
const int HX711_dout = 42; //mcu > HX711 dout pin
const int HX711_sck = 44; //mcu > HX711 sck pin
HX711_ADC LoadCell(HX711_dout, HX711_sck);
unsigned long t = 0;
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
//INIT RELAY
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
  //motors setup
  AFMS2.begin();
  AFMS3.begin();
  stop_motor(1);
  stop_motor(2);
  stop_motor(3);
  stop_teaball();
  stop_pump();
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
   float calibrationValue; // calibration value
  calibrationValue = -1710; // tested value 
  LoadCell.begin();
  unsigned long stabilizingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration factor (float)
    Serial.println("Startup is complete");
  }
  while (!LoadCell.update());
  Serial.println(LoadCell.getCalFactor());
  Serial.println(LoadCell.getConversionTime());
  Serial.println(LoadCell.getSPS());
  Serial.println(LoadCell.getSettlingTime());
  Serial.println("Note that the settling time may increase significantly if you use delay() in your sketch!");
  if (LoadCell.getSPS() < 7) {
    Serial.println("!!Sampling rate is lower than specification, check MCU>HX711 wiring and pin designations");
  }
  else if (LoadCell.getSPS() > 100) {
    Serial.println("!!Sampling rate is higher than specification, check MCU>HX711 wiring and pin designations");
  }
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

//  compute_weight();
  displayMenu();
}

void initialize_teararium(){

  
  initialize_arm();
  delay(5000);
//  initialize_crane();
  initialize_wagon();
  displace_wagon(3);
  unload_tea(3);
//  displace_wagon(1);
//  rotate_crane(2);
//  unsigned long StartTime = millis();
//  drop_teaball_down();
//  unsigned long CurrentTime = millis();
//  up_to_down_time = CurrentTime - StartTime;
//  Serial.print("Temps de descente : ");
//  Serial.println(up_to_down_time);
//  open_teaball();
//  displace_wagon(4);
//  activate_shovel();
//  displace_wagon(0);
//  close_teaball();
//  pull_teaball_up();
//  arm_smooth_down();
//  heat_thermoblock();
//  pour_water(100, false);
//  delay(2000);
//  arm_smooth_up();
//  rotate_crane(1);
//  immerge_teaball();
//  delay(180000);
//  pull_teaball_up();
//  delay(5000);
//  rotate_crane(0);
//  drop_teaball_down();
//  open_teaball();
//  delay(3000);
//  close_teaball();
//  pull_teaball_up();




  
////  initialize_arm();
//  displace_wagon(3);
////  delay(1000);
//  run_motor1();
//  displace_wagon(4);
//  activate_shovel();
//  displace_wagon(0);
//  pull_teaball_up();
//  delay(2500);
//  drop_teaball_down();
//  delay(1500);
//  open_teaball();
//  delay(3000);
//  close_teaball();
//    stir();
//    stop_stirring();
  //  arm_smooth_up();
//  prepare_tea(1);


}
