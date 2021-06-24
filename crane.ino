void initialize_crane(){
  Serial.println("jd");
   craneSwitchPinValue = digitalRead(craneSwitchPin);
   Serial.println("jff");
   while (craneSwitchPinValue != HIGH){
     craneSwitchPinValue = digitalRead(craneSwitchPin);
     AccelCranestepper.setMaxSpeed(1000);
     AccelCranestepper.setSpeed(50); 
     AccelCranestepper.runSpeed();
//     AccelCranestepper.run();
//     AccelCranestepper.setMaxSpeed(1500);
//     AccelCranestepper.setAcceleration(50);
//     AccelCranestepper.move(1);
//     Serial.println(craneSwitchPinValue);
}
    Serial.println("dada");
   craneSwitchPressed();
   Serial.println("Crane initialized");
}



void craneSwitchPressed(){
  Serial.println("Stop rotating the crane !!!");
  if (digitalRead(craneSwitchPin) == HIGH){
  craneStepper->release();
  }
} 
