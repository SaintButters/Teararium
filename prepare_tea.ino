void prepare_tea(int tea_index){
//  Serial.println("Starting Tea " + String(tea_index, 1) + " preparation");
  log_info("Starting Tea1 preparation", 1, 0 , 10);  

 Serial.println("couc");
 Serial.println(thermocouple1.readCelsius());
  Serial.println("coucou");
//  while (thermocouple1.readCelsius() < 110) {
  while (tea_index < 110) {

    displayTemperature(String(compute_temperature(),1));
    delay(1000);
  }
}

void unload_tea(int tea_index){
  float desired_tea_weight = 1;
  float timer_index=0;
  float tea_weight= 0;
  while (tea_weight < desired_tea_weight) {
    run_motor(tea_index, timer_index);
    tea_weight = compute_weight();
    delay(500);
    timer_index = timer_index + 500;
    if (timer_index == 3500)
      {timer_index = 0;}
    Serial.println(timer_index);
        }
  stop_motor(tea_index);
  }
