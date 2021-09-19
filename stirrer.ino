#include <Adafruit_MotorShield.h>
//INIT MOTEUR POMPE

void stir() {
  // put your setup code here, to run once:
  AFMS3.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  Serial.println("Starting stirring process");
//  run_pump();
//  StirrerMotor->setSpeed(100);
  StirrerMotor->run(FORWARD);
  Silo1Motor->setSpeed(125);
  Silo1Motor->run(BACKWARD);
  Silo1Motor->setSpeed(0);
  for (int i = 70; i <= 150; i++) {
    Serial.println(i);
    StirrerMotor->setSpeed(i);
    delay(60);
  }
  delay(22000);
  for (int i = 150; i >= 90; i--) {
    Serial.println(i);
    StirrerMotor->setSpeed(i);
    delay(1500);
  }
  delay(5000);
  StirrerMotor->setSpeed(0);
  delay(8000);
  for (int i = 70; i <= 100; i++) {
    Serial.println(i);
    StirrerMotor->setSpeed(i);
    delay(50);
  }
  delay(5000);
  StirrerMotor->setSpeed(0);
  delay(8000);
  for (int i = 70; i <= 100; i++) {
    Serial.println(i);
    StirrerMotor->setSpeed(i);
    delay(50);
  }
  delay(3500);
   for (int i = 70; i <= 85; i++) {
    Serial.println(i);
    StirrerMotor->setSpeed(i);
    delay(50);
  }
  delay(2000);
  StirrerMotor->setSpeed(0);
  delay(8000);
   for (int i = 70; i <= 85; i++) {
    Serial.println(i);
    StirrerMotor->setSpeed(i);
    delay(50);
  }
  delay(3000);
  StirrerMotor->setSpeed(0);
  delay(3000);
   for (int i = 70; i <= 85; i++) {
    Serial.println(i);
    StirrerMotor->setSpeed(i);
    delay(50);
  }
  delay(1500);
  StirrerMotor->setSpeed(0);
// 


}

void stop_stirring(){
  StirrerMotor->setSpeed(0);
  stop_pump();
  }
