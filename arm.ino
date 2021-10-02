
int current_angle;

void initialize_arm(){
  Serial.println("Initializing arm");
  arm_servo.write(180);
  arm_servo.attach(9);
//  if current_angle < arm_up_angle {
//    arm_smooth_down(arm_down_angle, current_angle);
//  }
//  else {
//    arm_smooth_up(current_angle, arm_up_angle);
//  }
//  }
//  arm_smooth_up(current_angle, arm_up_angle);
  Serial.println("arm initialized");
}

void arm_smooth_down(){
    arm_servo.attach(9);
    for (pos = 180; pos >=138; pos -=1) {
          arm_servo.write(pos);
          Serial.println(pos);
          delay(20);
          }
    arm_servo.detach();
    }

void arm_smooth_up (){
    arm_servo.attach(9);
    for (pos = 138; pos <=180; pos +=1) {
          arm_servo.write(pos);
          Serial.println(pos);
          delay(20);
          }
    arm_servo.detach();
    }
