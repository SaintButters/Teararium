void prepare_tea(int tea_index){
//  Serial.println("Starting Tea " + String(tea_index, 1) + " preparation");
  log_info("Starting Tea1 preparation", 1, 0 , 10);  
  while (thermocouple1.readCelsius() < 70) {
    Serial.println(thermocouple1.readCelsius());
    displayTemperature(String(computed_temperature(),1));
    delay(1000);
  }
}

void unload_tea(int tea_index){
//  delay(2000);
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
    Serial.print("a");
    analogWrite(switchPinled1, 255);
    analogWrite(switchPinled2, 0);
    analogWrite(switchPinled3, 0);
  }
  else if (large==HIGH){
        Serial.print("b");

    analogWrite(switchPinled1, 0);
    analogWrite(switchPinled2, 255);
    analogWrite(switchPinled3, 0);
  }
  else if (teapot==HIGH){
        Serial.print("c");

    analogWrite(switchPinled1, 0);
    analogWrite(switchPinled2, 0);
    analogWrite(switchPinled3, 255);
  }
}

void getTeaChoice(){
  int tea1 = digitalRead(Tea1switchPin);
  int tea2 = digitalRead(Tea2switchPin);
  int tea3 = digitalRead(Tea3switchPin);
  if (tea1==HIGH){
    Serial.println("Preparing Tea 1");
  }
  else if (tea2==HIGH){
    Serial.println("Preparing Tea 2");
  }
  else if (tea3==HIGH){
    Serial.println("Preparing Tea 3");
  }
}
