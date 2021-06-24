void prepare_tea(int tea_index){
  Serial.println("Starting Tea1 preparation");
  log_info("Starting Tea1 preparation", 1, 0 , 10);
  displace_wagon(tea_index);
  displace_wagon(0);
  
  delay(2000);

}
