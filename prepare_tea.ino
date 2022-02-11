

void prepare_tea(int tea_index){
  log_info("Starting Tea preparation", 1, 0 , 10);  
  initialize_arm();
  initialize_wagon();
  initialize_crane();
  displace_wagon(tea_index);
  unload_tea(tea_index);
  displace_wagon(1);
  rotate_crane(2);
  unsigned long StartTime = millis();
    drop_teaball_down();
  unsigned long CurrentTime = millis();
  up_to_down_time = CurrentTime - StartTime;
  Serial.print("Temps de descente : ");
  Serial.println(up_to_down_time);
  open_teaball();
  delay(2000); // test open teabull
  displace_wagon(4);
  activate_shovel();
  displace_wagon(0);
  close_teaball();
  pull_teaball_up();
  arm_smooth_down();
  pour_water(325, true);
  delay(1000);
  arm_smooth_up();
  delay(1000);
  rotate_crane(1);
  immerge_teaball();
  infusing_timer(180);
  pull_teaball_up();
  delay(30000);
  rotate_crane(0);
  drop_teaball_down();
  open_teaball();
}

void unload_tea(int tea_index){

  float desired_tea_weight = 2;
  float timer_index=0;
  float tea_weight= 0;
  float initial_mesure = 0;
  int timer =0;
  int roll_timer =0;
  int sense =0;
  init_scale();
  initial_mesure = compute_weight();
  while (tea_weight < desired_tea_weight + initial_mesure) {
//   while (roll_timer < 35) {
    timer = timer + 1;
    roll_timer = roll_timer +1;
    tea_weight = compute_weight();
    delay(250); 
    if (timer == 4){
      if (sense == 0){
        sense = 1;
      }
      else {
        sense = 0;
      }
      run_motor(tea_index, sense);
      timer = 0;
      }
    }
  stop_motor(tea_index);
  }

void infusing_timer(int seconds){
  int timer = seconds;
  int wiggle_timer = 0;
  while (timer != -1){
      display_timer(timer);
      if (wiggle_timer == 20){
        CraneMotor->setSpeed(100);
        CraneMotor->run(BACKWARD);
      }
      if (wiggle_timer == 21){
        CraneMotor->setSpeed(100);
        CraneMotor->run(FORWARD);
        wiggle_timer =0;
      }
      delay(1000);
      timer = timer - 1;
      wiggle_timer = wiggle_timer +1;
      CraneMotor->setSpeed(0);
      Serial.println(timer);
    }
}

void getTeaSize(){
  int small = digitalRead(smallCupSwitchPin);
  int large = digitalRead(largeCupSwitchPin);
  int teapot = digitalRead(teapotSwitchPin);
  if (small==HIGH){
    log_info("Small cup selected", 1, 0 , 10);
    analogWrite(switchPinled1, 255);
    analogWrite(switchPinled2, 0);
    analogWrite(switchPinled3, 0);
    TeaSize = 1;
    delay(1500);
  }
  else if (large==HIGH){
    log_info("Large cup selected", 1, 0 , 10);
    analogWrite(switchPinled1, 0);
    analogWrite(switchPinled2, 255);
    analogWrite(switchPinled3, 0);
    TeaSize = 2;
    delay(1500);
  }
  else if (teapot==HIGH){
    log_info("Teapot selected", 1, 0 , 10);
    analogWrite(switchPinled1, 0);
    analogWrite(switchPinled2, 0);
    analogWrite(switchPinled3, 255);
    TeaSize = 3;
    delay(1500);
  }
}

void getTeaChoice(){
  int tea1 = digitalRead(Tea1switchPin);
  int tea2 = digitalRead(Tea2switchPin);
  int tea3 = digitalRead(Tea3switchPin);
  if (tea1==HIGH){
    if (TeaSize == 0){
      log_info("Please select a Tea size :)", 1, 0 , 10);  
      delay(2000);
    }
    else{
    Serial.println("Preparing Tea 1");
    prepare_tea(1);
    }
  }
  else if (tea2==HIGH){
    if (TeaSize == 0){
      log_info("Please select a Tea size :)", 1, 0 , 10);  
      delay(2500);
    }
    else{
    Serial.println("Preparing Tea 2");
    prepare_tea(2);
    }
  }
  else if (tea3==HIGH){
    
    if (TeaSize == 0){
      log_info("Please select a Tea size :)", 1, 0 , 10);  
      delay(2500);
    }
    else{
    Serial.println("Preparing Tea 3");
    prepare_tea(3);
    }
  }
}
