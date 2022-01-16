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
  float desired_tea_weight = 3;
  float timer_index=0;
  float tea_weight= 0;
  float initial_mesure = 0;
  int timer =0;
  int sense =0;
  init_scale();
  initial_mesure = compute_weight();
  while (tea_weight < desired_tea_weight + initial_mesure) {
    timer = timer + 1;
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
    while (timer != -1){
      display_timer(timer);
      delay(1000);
      timer = timer - 1;
      Serial.println(timer);
    }
}
