void initialize_wagon(){
  Serial.println("Starting Wagon initialization");
  AFMS2.begin();
  TWBR = ((F_CPU /400000l) - 16) / 2; // Change the i2c clock to 400KHz
  wagonSwitchPinValue = digitalRead(wagonSwitchPin);
   while (wagonSwitchPinValue != HIGH){
     wagonSwitchPinValue = digitalRead(wagonSwitchPin);
     AccelWagonstepper.setMaxSpeed(1500);
     AccelWagonstepper.setSpeed(-1500); 
     AccelWagonstepper.runSpeed(); 
}
   wagonSwitchPressed();
   WagonHomePosition = AccelWagonstepper.currentPosition();
   shovel_servo.attach(11);
   shovel_servo.write(0);
   delay(500);
   shovel_servo.detach();
   Serial.println(WagonHomePosition);
//   AccelWagonstepper.disableOutputs();
   Serial.println("Wagon initialized");
}

void wagonSwitchPressed(){
  Serial.println("Stop rolling the wagon!!!");
  if (digitalRead(wagonSwitchPin) == HIGH){
  wagonStepper->release();
  }
}  

void displace_wagon(int tea_index){
  AFMS2.begin();
  TWBR = ((F_CPU /400000l) - 16) / 2; // Change the i2c clock to 400KHz
  AccelWagonstepper.setMaxSpeed(1500.0);
  AccelWagonstepper.setAcceleration(250.0);
  if (tea_index==0){
    WagonDestination = WagonHomePosition;
    
  }
  else if (tea_index==4){
//    WagonDestination = WagonHomePosition + 290;
WagonDestination = WagonHomePosition + 4100;
    
  }
  else {
//    WagonDestination = WagonHomePosition + 20 + (tea_index - 1) * 355;
WagonDestination = WagonHomePosition + 400 + (tea_index - 1) * 5450;
  }
  AccelWagonstepper.moveTo(WagonDestination);
  Serial.println(WagonHomePosition);
  
  while (AccelWagonstepper.currentPosition() != WagonDestination) {   
   AccelWagonstepper.runToNewPosition(WagonDestination);
   Serial.println(AccelWagonstepper.currentPosition());
  }
//   AccelWagonstepper.setMaxSpeed(500); // divide by 3 to get rpm
//   AccelWagonstepper.setAcceleration(80);
//   AccelWagonstepper.moveTo(-500);
//   AccelWagonstepper.run();
   wagonStepper->release();
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
