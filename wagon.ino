void initialize_wagon(){
  Serial.println("Starting Wagon initialization");
  wagonSwitchPinValue = digitalRead(wagonSwitchPin);
  wagonStepper.enableOutputs();
   while (wagonSwitchPinValue != HIGH){
      wagonSwitchPinValue = digitalRead(wagonSwitchPin);
      wagonStepper.setSpeed(1500);
      wagonStepper.runSpeed();
  }
   wagonSwitchPressed();
   WagonHomePosition = wagonStepper.currentPosition();
   shovel_servo.attach(11);
   shovel_servo.write(0);
   delay(500);
   shovel_servo.detach();
   Serial.println(WagonHomePosition);
   Serial.println("Wagon initialized");
}

void wagonSwitchPressed(){
  Serial.println("Stop rolling the wagon!!!");
  delay(50);
  if (digitalRead(wagonSwitchPin) == HIGH){
    wagonStepper.disableOutputs();
  }
}  

void displace_wagon(int tea_index){

  wagonStepper.enableOutputs();
  if (tea_index==0){
    WagonDestination = WagonHomePosition;
    
  }
  else if (tea_index==4){
    Serial.println("Wagon going to filling");
    WagonDestination = WagonHomePosition - 2250;
  }
  else {
    WagonDestination = WagonHomePosition - 275 - (tea_index - 1) * 2840;
  }
  wagonStepper.moveTo(WagonDestination);
  Serial.println(WagonHomePosition);
  while (wagonStepper.currentPosition() != WagonDestination) {   
   wagonStepper.runToNewPosition(WagonDestination);
   Serial.println(wagonStepper.currentPosition());
  }
  wagonStepper.disableOutputs();

}

float compute_weight() {

    float weight;
    LoadCell.update(); // retrieves data from the load cell
    weight = LoadCell.getData(); // get output value
    Serial.print(weight); // print out the retrieved value to the second row
    Serial.println(" grams"); // print out the retrieved value to the second row
    displayWeight(String(weight,2));
    return weight; 
}
