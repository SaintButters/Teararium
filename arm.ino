
int current_angle;

void initialize_arm(){
  Serial.println("Initializing arm");
  current_angle = arm_servo.read();
//  if current_angle < arm_up_angle {
//    arm_smooth_down(arm_down_angle, current_angle);
//  }
//  else {
//    arm_smooth_up(current_angle, arm_up_angle);
//  }
//  }
  arm_smooth_up(current_angle, arm_up_angle);
  Serial.println("arm initialized");
}

void arm_smooth_down(int ending_angle, int starting_angle){
    arm_servo.attach(9);
    for (pos = ending_angle; pos >=starting_angle; pos -=1) {
          arm_servo.write(pos);
          Serial.println(pos);
          delay(15);
          }
    arm_servo.detach();
    }

void arm_smooth_up (int ending_angle, int starting_angle){
    arm_servo.attach(9);
    for (pos = ending_angle; pos <=starting_angle; pos +=1) {
          arm_servo.write(pos);
          Serial.println(pos);
          delay(15);
          }
    arm_servo.detach();
    }
