void initialize_wagon(){
  Serial.println("Starting Wagon initialization");
   wagonSwitchPinValue = digitalRead(wagonSwitchPin);
   while (wagonSwitchPinValue != HIGH){
     wagonSwitchPinValue = digitalRead(wagonSwitchPin);
     AccelWagonstepper.setMaxSpeed(1000);
     AccelWagonstepper.setSpeed(-50); 
     AccelWagonstepper.runSpeed();
}
   wagonSwitchPressed();
   WagonHomePosition = AccelWagonstepper.currentPosition();
     shovel_servo.attach(11);
   shovel_servo.write(0);
   shovel_servo.detach();
   Serial.println(WagonHomePosition);
   Serial.println("Wagon initialized");
}

void wagonSwitchPressed(){
  Serial.println("Stop rolling the wagon!!!");
  if (digitalRead(wagonSwitchPin) == HIGH){
  wagonStepper->release();
  
  }
}  

void displace_wagon(int tea_index){
  AccelWagonstepper.setMaxSpeed(100.0);
  AccelWagonstepper.setAcceleration(50.0);
  if (tea_index==0){
    WagonDestination = WagonHomePosition;
    
  }
  else if (tea_index==4){
    WagonDestination = WagonHomePosition + 350;
    
  }
  else {
    WagonDestination = WagonHomePosition + 20 + (tea_index - 1) * 320;
  }
  AccelWagonstepper.moveTo(WagonDestination);
  Serial.println(WagonHomePosition);
  
  while (AccelWagonstepper.currentPosition() != WagonDestination) {
   Serial.println("yololoolol");
   
   AccelWagonstepper.runToNewPosition(WagonDestination);
   Serial.println(AccelWagonstepper.currentPosition());
  }
//   AccelWagonstepper.setMaxSpeed(500); // divide by 3 to get rpm
//   AccelWagonstepper.setAcceleration(80);
//   AccelWagonstepper.moveTo(-500);
//   AccelWagonstepper.run();
   Serial.println("dollll");
   wagonStepper->release();
}
