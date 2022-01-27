void initialize_crane(){
  Serial.println("Intializing crane");
   teaball_servo.write(closed_teaball_angle);
   init_closed_teaball();
   pull_teaball_up();
   Serial.println("Rotating crane to home");
   craneSwitchPinValue = digitalRead(craneSwitchPin);
   craneStepper.enableOutputs();
   while (craneSwitchPinValue != HIGH){
     craneSwitchPinValue = digitalRead(craneSwitchPin);
     craneStepper.setSpeed(-3500);
     craneStepper.runSpeed();
    }
   CraneHomePosition = craneStepper.currentPosition();
   craneSwitchPressed();
   Serial.println("Crane initialized");
}


void craneSwitchPressed(){
  Serial.println("Stop rotating the crane !!!");
  if (digitalRead(craneSwitchPinValue) == HIGH){
    rotate_crane(0);
//    craneStepper.disableOutputs();
  }
} 
 void init_closed_teaball(){
  teaball_servo.write(closed_teaball_angle);
  teaball_servo.attach(8);
  delay(500);
  teaball_servo.detach();
 }
void open_teaball(){
  teaball_servo.attach(8);
  for (pos = closed_teaball_angle; pos >= open_teaball_angle; pos -=1) {
    teaball_servo.write(pos);
    delay(8);
  }
  teaball_servo.detach();
}


void close_teaball(){   
  teaball_servo.attach(8);
  for (pos =open_teaball_angle; pos <= closed_teaball_angle; pos +=1) {
    teaball_servo.write(pos);
    delay(8);
  }
 teaball_servo.detach();
 }

void pull_teaball_up(){
  Serial.println("Pulling teaball up");
  TeaBallUpSwitchValue = digitalRead(TeaBallUpSwitchPin);
//    CraneMotor->setSpeed(50);
  CraneMotor->setSpeed(200);
  while (TeaBallUpSwitchValue !=HIGH){
    TeaBallUpSwitchValue = digitalRead(TeaBallUpSwitchPin);
    CraneMotor->run(BACKWARD);
  }
  CraneMotor->setSpeed(0);
  }

void drop_teaball_down(){
  Serial.println("Pulling teaball down");
  TeaBallDownSwitchValue = digitalRead(TeaBallDownSwitchPin);
    //    CraneMotor->setSpeed(50);
  CraneMotor->setSpeed(200);
  while (TeaBallDownSwitchValue !=HIGH){
    TeaBallDownSwitchValue = digitalRead(TeaBallDownSwitchPin);
    CraneMotor->run(FORWARD);
  }
  CraneMotor->setSpeed(0);
  }

void stop_teaball(){
  
  CraneMotor->setSpeed(0);
}

void immerge_teaball(){
  Serial.println("Immerging teaball");
    // create with the default frequency 1.6KHz
  CraneMotor->setSpeed(100);
  CraneMotor->run(FORWARD);
  delay(up_to_down_time*1.15);
  CraneMotor->setSpeed(0);
  }

 void rotate_crane(int step_index){
  if (step_index==0){
    CraneDestination = CraneHomePosition + 100;
    
  }
  else if (step_index==1){
    CraneDestination = CraneHomePosition + 305;

  }
  else{
//        CraneDestination = CraneHomePosition  + 335;.
      CraneDestination = CraneHomePosition  + 460;

  }
  craneStepper.enableOutputs();
    while (craneStepper.currentPosition() != CraneDestination) {
        craneStepper.runToNewPosition(CraneDestination);
    }
//  craneStepper.disableOutputs();
}
