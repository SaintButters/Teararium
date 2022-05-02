float infusingTime[4] = {320, time1*60, time2*60, time3*60};
float infusingFactor[4] = {0, 1, 1, 1.5};
float waterVolume[4] = {0, 120, 200, 500};
float teaWeight[4] = {0, 1.5, 1.75, 2.5};
boolean enough_tea = false;
boolean enough_water = false;

void prepare_tea(int tea_index, int tea_size){
  float infusingTime[4] = {320, time1*60, time2*60, time3*60};
  int infusingTemp[4] = {0, temp1, temp2, temp3};
  Serial.println(infusingTime[tea_index]);
  Serial.println(infusingFactor[tea_size]);
  Serial.println(infusingTemp[tea_index]);
  Serial.println(waterVolume[tea_size]);
  Serial.println(teaWeight[tea_size]);
  log_info("Starting Tea preparation", 1, 0 , 10);  
  turn_buttons_leds_off_preparation(tea_index);
  initialize_arm();
  initialize_wagon();
  initialize_crane(true);
  load_tea(tea_index, tea_size);
  if (enough_tea == false) {
    initialize_crane(false);
    Serial.println("Tea Box empty. Preparation ended");
  }
  else {
    fill_cup(tea_index, tea_size);
    if (enough_water == false) {
      Serial.println("Water tank empty. Preparation ended");
      initialize_crane(false);
    }
    else {
      pull_teaball_up();
      infuse_tea(tea_index, tea_size, false);
    }
  drop_teaball_down();
  open_teaball();
  }  
  turn_buttons_leds_on();
}

void prepare_previous_tea(int tea_index, int tea_size){

  Serial.println(infusingTime[tea_index]);
  Serial.println(infusingFactor[tea_size]);
  Serial.println(infusingTemp[tea_index]);
  Serial.println(waterVolume[tea_size]);
  Serial.println(teaWeight[tea_size]);
  log_info("Starting Tea preparation :   Re-use", 1, 0 , 10);    
  turn_buttons_leds_off_preparation(0);
  initialize_arm();
  initialize_wagon();
  initialize_crane(true);
  fill_cup(0, tea_size);
  if (enough_water == false) {
    Serial.println("Water tank empty. Preparation ended");
    initialize_crane(false);
  }
  else{
    pull_teaball_up();
    infuse_tea(0, tea_size, true);
    drop_teaball_down();
    open_teaball();
  }
  turn_buttons_leds_on();
}


void test_prepare_tea(int tea_index, int tea_size){
  float infusingTime[4] = {320, time1*60, time2*60, time3*60};
  int infusingTemp[4] = {0, temp1, temp2, temp3};
  Serial.println(infusingTime[tea_index]);
  Serial.println(infusingFactor[tea_size]);
  Serial.println(infusingTemp[tea_index]);
  Serial.println(waterVolume[tea_size]);
  Serial.println(teaWeight[tea_size]);
  log_info("Starting Tea preparation", 1, 0 , 10);  
  turn_buttons_leds_off_preparation(tea_index);
  initialize_arm();
  initialize_wagon();
  initialize_crane(true);
  rotate_crane(2);
  if (powered==false){
    return;
  }
  drop_teaball_down();
  if (powered==false){
  return;
  }
  if (powered==false){
    return;
  }
  open_teaball();
  if (powered==false){
    return;
  }
  delay(500); 
  displace_wagon(4);
  if (powered==false){
    return;
  }
  activate_shovel();
  if (powered==false){
    return;
  }
  displace_wagon(0);
  if (powered==false){
    return;
  }
  close_teaball();
  if (powered==false){
    return;
  }
  pull_teaball_up();
  if (powered==false){
    return;
  }
  rotate_crane(1);
  if (powered==false){
    return;
  }
  immerge_teaball();
  delay(4000);
  pull_teaball_up();
  if (powered==false){
    return;
  }
  if (powered==false){
    return;
  }
  rotate_crane(0);
  if (powered==false){
    return;
  }
  drop_teaball_down();
  if (powered==false){
    return;
  }
  open_teaball();
  turn_buttons_leds_on();
  
}

void load_tea(int tea_index, int tea_size){
  displace_wagon(tea_index);
//  if (powered==false){
//    return;
//  }
  unload_tea(tea_index, tea_size);
//  if (powered==false){
//    return;
//  }
  displace_wagon(1);
//  if (enough_tea == false) {
//    return;
//  }
  if (powered==false){
    return;
  }
  rotate_crane(2);
  if (powered==false){
    return;
  }
  drop_teaball_down();
  if (powered==false){
  return;
  }
  if (powered==false){
    return;
  }
  open_teaball();
  if (powered==false){
    return;
  }
  delay(500); 
  displace_wagon(4);
  if (powered==false){
    return;
  }
  activate_shovel();
  if (powered==false){
    return;
  }
  displace_wagon(0);
  if (powered==false){
    return;
  }
  close_teaball();
  if (powered==false){
    return;
  }
  pull_teaball_up();
  if (powered==false){
    return;
  }
}

void fill_cup(int tea_index, int tea_size){
  arm_smooth_down();
  if (powered==false){
    return;
  }
  pour_water(tea_index, tea_size, true, true);
  if (powered==false){
    return;
  }
  delay(1000);
  if (powered==false){
    return;
  }
  arm_smooth_up();
  if (powered==false){
    return;
  }
  delay(1000);
}

void infuse_tea(int tea_index, int tea_size, boolean reuse){
  rotate_crane(1);
  if (powered==false){
    return;
  }
  immerge_teaball();
  if (powered==false){
    return;
  }
  if (reuse == true){
    infusing_timer(infusingTime[tea_index]*infusingFactor[tea_size]*1.5);
  }
  else {
    infusing_timer(infusingTime[tea_index]*infusingFactor[tea_size]);
  }
  if (powered==false){
    return;
  }
  pull_teaball_up();
  if (powered==false){
    return;
  }
  delay(10000);
  if (powered==false){
    return;
  }
  rotate_crane(0);
}


void unload_tea(int tea_index, int tea_size){

  float desired_tea_weight = teaWeight[tea_size];
  Serial.print("Tea size = ");
  Serial.println(tea_size);
  Serial.print("Tea weight = ");
  Serial.println(desired_tea_weight);
  float timer_index=0;
  float tea_weight= 0;
  float initial_mesure = 0;
  int timer =0;
  int roll_timer =0;
  int sense =0;
  enough_tea = false;
  init_scale();
  initial_mesure = compute_weight();
  unsigned long unloadingTime= 0;
  unsigned long CurrentTime;
  unsigned long StartTime = millis();
  Serial.print("StartTime :");
  Serial.println(StartTime);
  while (tea_weight < desired_tea_weight + initial_mesure) {
//  while (unloadingTime < 4850*infusingFactor[tea_size]) {
    Serial.print("CurrentTime :");
    Serial.println(CurrentTime);
    Serial.print("unloadingTime :");
    Serial.println(unloadingTime);
    CurrentTime = millis();
    unloadingTime = CurrentTime - StartTime;
    if (powered==false){
        stop_motor(tea_index);
        return;
      }
    if (tea_weight > 10 or tea_weight <-10){
      Serial.println("Measure error. Abord");
      stop_motor(tea_index);
      return;
    }
    timer = timer + 1;
    roll_timer = roll_timer +1;
    tea_weight = compute_weight();
    delay(250); 
    if (unloadingTime > 15000){
        Serial.println("Max loading time exceeded. Loading ended");
        stop_motor(tea_index);
        break;
      }
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
  if (tea_weight > 0.66 * desired_tea_weight){
    enough_tea = true;
    }
  }

void infusing_timer(int seconds){
  int timer = seconds;
  int wiggle_timer = 0;
  while (timer != -1){
      if (powered==false){
        return;
      }
      display_timer(timer);
//      if (wiggle_timer == 20){
//        CraneMotor->setSpeed(70);
//        CraneMotor->run(BACKWARD);
//      }
//      if (wiggle_timer == 21){
//        CraneMotor->setSpeed(55);
//        CraneMotor->run(FORWARD);
//        wiggle_timer =0;
//      }
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
    delay(250);
  }
  else if (large==HIGH){
    log_info("Large cup selected", 1, 0 , 10);
    analogWrite(switchPinled1, 0);
    analogWrite(switchPinled2, 255);
    analogWrite(switchPinled3, 0);
    TeaSize = 2;
    delay(250);
  }
  else if (teapot==HIGH){
    log_info("Teapot selected", 1, 0 , 10);
    analogWrite(switchPinled1, 0);
    analogWrite(switchPinled2, 0);
    analogWrite(switchPinled3, 255);
    TeaSize = 3;
    delay(250);
  }
}

void getTeaChoice(){
  int tea1 = digitalRead(Tea1switchPin);
  int tea2 = digitalRead(Tea2switchPin);
  int tea3 = digitalRead(Tea3switchPin);
  boolean reuse_tea = false;
  unsigned long starttime;
  unsigned long endtime;
  if (tea1==HIGH){
    if (TeaSize == 0){
      log_info("Please select a Tea size", 1, 0 , 10);  
      delay(2500);
    }
    else{
      Serial.println("Preparing Tea 1");
      delay(250);
      prepare_tea(1, TeaSize);
      }
    }
  else if (tea2==HIGH){
    if (TeaSize == 0){
      log_info("Please select a Tea size", 1, 0 , 10);  
      delay(2500);
    }
    else{
        starttime = millis();
        endtime = starttime;
        while ((endtime - starttime) <=750){
          tea3 = digitalRead(Tea3switchPin);
          if (tea3==HIGH){
            reuse_tea = true;
            break;
          }
          endtime = millis();
        }
        if(reuse_tea==false){
          Serial.println("Preparing Tea 2");
          prepare_tea(2, TeaSize);
        }
        else{
          Serial.println("Re-using last teaball");
          prepare_previous_tea(0, TeaSize);
        }
    }
  }
  else if (tea3==HIGH){
    if (TeaSize == 0){
      log_info("Please select a Tea size", 1, 0 , 10);  
      delay(2500);
    }
    else{
      starttime = millis();
        endtime = starttime;
        while((endtime - starttime) <=750){
          tea2 = digitalRead(Tea2switchPin);
          if (tea2==HIGH){
            reuse_tea = true;
            break;
          }
          endtime = millis();
        }
        if(reuse_tea==false){
          Serial.println("Preparing Tea 3");
          prepare_tea(3, TeaSize);
      }
    }
  }
}
