void prepare_tea(int tea_index){
//  Serial.println("Starting Tea " + String(tea_index, 1) + " preparation");
  log_info("Starting Tea1 preparation", 1, 0 , 10);
  delay(1500);
  
//  displace_wagon(tea_index);
//  displace_wagon(0);
 Serial.println("couc");
 Serial.println(thermocouple.readCelsius());
  Serial.println("coucou");
//  while (thermocouple.readCelsius() < 110) {
  while (tea_index < 110) {

//    displayTemperature(String(thermocouple.readCelsius(),1));
     Serial.println(thermocouple.readCelsius());
     delay(500);
  }
}
