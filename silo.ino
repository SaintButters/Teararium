#include <Adafruit_MotorShield.h>
void run_motor(int tea_index, int sense) {
  if(tea_index == 1){
    Serial.println("Activating silo motor 1");
    Silo1Motor->setSpeed(230);
    if (sense == 0){
      Silo1Motor->run(FORWARD);
      }
    else {
      Silo1Motor->run(BACKWARD);
      }
  }
  else if (tea_index == 2){
    Serial.println("Activating silo motor 2");
    Silo2Motor->setSpeed(230);
    if (sense == 0){
      Silo2Motor->run(FORWARD);
      }
    else {
      Silo2Motor->run(BACKWARD);
      }
  }
  else if (tea_index == 3){
    Serial.println("Activating silo motor 3");
    Silo3Motor->setSpeed(215);
    if (sense == 0){
      Silo3Motor->run(FORWARD);
      }
    else {
      Silo3Motor->run(BACKWARD);
      }
  }
}

void stop_motor(int tea_index) {
  
  if(tea_index == 1){
    Serial.println("stopping silo motor1");
    Silo1Motor->setSpeed(0);
    }
  else if (tea_index == 2){
    Serial.println("stopping silo motor2");
    Silo2Motor->setSpeed(0);
    }
  else if (tea_index == 3){
    Serial.println("stopping silo motor3");
    Silo3Motor->setSpeed(0);
    }
}

  
