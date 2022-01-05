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
  init_scale();
  while (tea_weight < desired_tea_weight) {
//  while (tea_weight < 10000) {
    run_motor(tea_index);
    tea_weight = compute_weight();
//    timer_index = timer_index + 500;
    
//    if (timer_index == 3500)
//      {timer_index = 0;}

//  run_motor(tea_index, timer_index);
  }
//  delay(13000);

  
  stop_motor(tea_index);
  }
