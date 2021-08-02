void prepare_tea(int tea_index){
//  Serial.println("Starting Tea " + String(tea_index, 1) + " preparation");
  log_info("Starting Tea1 preparation", 1, 0 , 10);
  delay(1500);
  
//  displace_wagon(tea_index);
//  displace_wagon(0);
  while (thermocouple.readCelsius() < 200) {
    displayTemperature(String(thermocouple.readCelsius(),1));
  }
}
