
#include <Adafruit_MotorShield.h>

//INIT MOTEUR POMPE
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
//int motorState = 0;

void run_motor1() {
  // put your setup code here, to run once:
  AFMS2.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
//  myMotor->run(FORWARD);
//  delay(3000);
//  myMotor->setSpeed(0);
//  delay(1000);
  SiloMotor1->setSpeed(75);
  SiloMotor1->run(BACKWARD);
  delay(3000);
  SiloMotor1->run(FORWARD);
  delay(1500);
  SiloMotor1->run(BACKWARD);
  delay(2000);
  SiloMotor1->run(FORWARD);
  delay(500);
  SiloMotor1->setSpeed(0);
}
