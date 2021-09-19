#include <Adafruit_MotorShield.h>

void run_motor(int tea_index, int timer_index) {
//  if(tea_index = 1){
//    motor = Silo1Motor}
//  else if (tea_nb = 2){
//    motor = Silo2Motor}
//  else if (tea_nb = 3){
//    motor = Silo3Motor}
//  AFMS2.begin();  // create with the default frequency 1.6KHz
//  motor->setSpeed(75);
//  motor->run(BACKWARD);
//  delay(3000);
//  motor->run(FORWARD);
//  delay(1500);
//  motor->run(BACKWARD);
//  delay(2000);
//  motor->run(FORWARD);
//  delay(500);
  AFMS2.begin();
  int motor_speed = 125;
  
  if(tea_index == 1){
    Silo1Motor->setSpeed(motor_speed);
    if (timer_index <= 2000){
    Silo1Motor->run(BACKWARD);
    }
    else {
      Silo1Motor->run(FORWARD);
    }
  }
  else if (tea_index == 2){
    Silo2Motor->setSpeed(motor_speed);
     if (timer_index <= 2000){
    Silo2Motor->run(BACKWARD);
    }
    else {
      Silo2Motor->run(FORWARD);
    }
  }
  else if (tea_index == 3){
    Silo3Motor->setSpeed(motor_speed);
    if (timer_index <= 2000){
      Silo3Motor->run(BACKWARD);
    }
    else {
      Silo3Motor->run(FORWARD);
    }
    }
}

void stop_motor(int tea_index) {
  if(tea_index == 1){
    Silo1Motor->setSpeed(0);
    }
  else if (tea_index == 2){
    Silo2Motor->setSpeed(0);
    }
  else if (tea_index == 3){
    Silo3Motor->setSpeed(0);
    }
}

  
