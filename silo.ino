#include <Adafruit_MotorShield.h>
void run_motor(int tea_index) {
  Serial.println(tea_index);
  if(tea_index == 1){
    Serial.println("Activating silo motor 1");
    Silo1Motor->setSpeed(230);
    Silo1Motor->run(FORWARD);
  }
  else if (tea_index == 2){
    Serial.println("Activating silo motor 2");
    Silo2Motor->setSpeed(230);
    Silo2Motor->run(FORWARD);
  }
  else if (tea_index == 3){
    Serial.println("Activating silo motor 3");
    Silo3Motor->setSpeed(230);
    Silo3Motor->run(FORWARD);
  }
//  int motor_speed = 125;
//  Silo3Motor->setSpeed(200);
//  Silo3Motor->run(FORWARD);

//  delay(3000);
//  motor->run(FORWARD);
//  delay(1500);
//  motor->run(BACKWARD);
//  delay(2000);
//  motor->run(FORWARD);
//  delay(500);
    
  
//  
//  if(tea_index == 1){
//    Silo1Motor->setSpeed(motor_speed);
//    if (timer_index <= 1750){
//    Silo1Motor->run(BACKWARD);
//    }
//    else {
//      Silo1Motor->run(FORWARD);
//    }
//  }
//  else if (tea_index == 2){
//    Silo2Motor->setSpeed(motor_speed);
//     if (timer_index <= 1750){
//    Silo2Motor->run(BACKWARD);
//    }
//    else {
//      Silo2Motor->run(FORWARD);
//    }
//  }
//  else if (tea_index == 3){
//    Silo3Motor->setSpeed(motor_speed);
//    if (timer_index <= 2000){
//      Silo3Motor->run(BACKWARD);
//    }
//    else {
//      Silo3Motor->run(FORWARD);
//    }
//    }
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

  
