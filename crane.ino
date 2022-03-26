void initialize_crane(boolean tea_prep){
   Serial.println("Intializing crane");
   close_teaball();
   pull_teaball_up();
   Serial.println("Rotating crane to home");
   craneSwitchPinValue = digitalRead(craneSwitchPin);
   craneStepper.enableOutputs();
   while (craneSwitchPinValue != HIGH){
    if (turn_off == true){
        return;
      }
     craneSwitchPinValue = digitalRead(craneSwitchPin);
     craneStepper.setSpeed(-3500);
     craneStepper.runSpeed();
    }
   CraneHomePosition = craneStepper.currentPosition();
   craneSwitchPressed();
   if (tea_prep == false){
    drop_teaball_down();
    open_teaball();
   }
   Serial.println("Crane initialized");
}


void craneSwitchPressed(){
  Serial.println("Stop rotating the crane !!!");
  if (digitalRead(craneSwitchPinValue) == HIGH){
    rotate_crane(0);
  }
} 

void open_teaball(){
  if (teaball_open==false){
    Serial.println("Opening teaball");
    teaball_servo.attach(8);
    for (pos = closed_teaball_angle; pos >= open_teaball_angle; pos -=1) {
      teaball_servo.write(pos);
      delay(8);
    }
    teaball_servo.detach();
    teaball_open = true;
  }
  
}

void close_teaball(){   
  if (teaball_open==true){
    Serial.println("Closing teaball");
    teaball_servo.attach(8);
    for (pos =open_teaball_angle; pos <= closed_teaball_angle; pos +=1) {
      teaball_servo.write(pos);
      delay(8);
    }
   teaball_servo.detach();
   teaball_open = false;
  }
 }

 void init_close_teaball(){
     Serial.println("Init : closing teaball");
     teaball_servo.attach(8);
     teaball_servo.write(closed_teaball_angle);
     delay(2000);
     teaball_servo.detach();
     
 }

void pull_teaball_up(){
  Serial.println("Pulling teaball up");
  TeaBallUpSwitchValue = digitalRead(TeaBallUpSwitchPin);
  CraneMotor->setSpeed(200);
  while (TeaBallUpSwitchValue !=HIGH){
    if (turn_off == true){
        CraneMotor->setSpeed(0);
        return;
      }
    TeaBallUpSwitchValue = digitalRead(TeaBallUpSwitchPin);
    CraneMotor->run(BACKWARD);
  }
  CraneMotor->setSpeed(0);
  }

void drop_teaball_down(){
  Serial.println("Pulling teaball down");
  TeaBallDownSwitchValue = digitalRead(TeaBallDownSwitchPin);
  CraneMotor->setSpeed(200);
  while (TeaBallDownSwitchValue !=HIGH){
    if (turn_off == true){
        CraneMotor->setSpeed(0);
        return;
      }
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
  delay(up_to_down_time*0.5);
  CraneMotor->setSpeed(50);
  delay(up_to_down_time*1.5);
  CraneMotor->setSpeed(0);
  }

 void rotate_crane(int step_index){
  Serial.print("Rotating crane to : ");
  Serial.println(step_index);
  if (step_index==0){
//    CraneDestination = CraneHomePosition + 95;
CraneDestination = CraneHomePosition + 30;
    
  }
  else if (step_index==1){
    CraneDestination = CraneHomePosition + 250;

  }
  else{
      CraneDestination = CraneHomePosition  + 410;
  }
  craneStepper.enableOutputs();
    while (craneStepper.currentPosition() != CraneDestination) {
        if (turn_off == true){
        craneStepper.disableOutputs();
        return;
      }
        craneStepper.runToNewPosition(CraneDestination);
    }
    Serial.println("Crane rotation completed");
//  craneStepper.disableOutputs();
}
