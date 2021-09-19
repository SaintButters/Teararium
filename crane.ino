void initialize_crane(){
  Serial.println("Intializing crane");
   close_teaball();
   pull_teaball_up();
   craneSwitchPinValue = digitalRead(craneSwitchPin);
   while (craneSwitchPinValue != HIGH){
     craneSwitchPinValue = digitalRead(craneSwitchPin);
     AccelCranestepper.setMaxSpeed(1000);
     AccelCranestepper.setSpeed(200); 
     AccelCranestepper.runSpeed();
    }
   craneSwitchPressed();
   CraneHomePosition = AccelCranestepper.currentPosition();
   Serial.println("Crane initialized");
}


void craneSwitchPressed(){
  Serial.println("Stop rotating the crane !!!");
  if (digitalRead(craneSwitchPinValue) == HIGH){
  craneStepper->release();
  }
} 

void open_teaball(){
  teaball_servo.attach(12);
  for (pos = closed_teaball_angle; pos >= open_teaball_angle; pos -=1) {
    teaball_servo.write(pos);
    delay(8);
  }
  teaball_servo.detach();
}


void close_teaball(){   
  teaball_servo.attach(12);
  for (pos =open_teaball_angle; pos <= closed_teaball_angle; pos +=1) {
    teaball_servo.write(pos);
    delay(8);
  }
 teaball_servo.detach();
 }

void pull_teaball_up(){
  Serial.println("Pulling teaball up");
  TeaBallUpSwitchValue = digitalRead(TeaBallUpSwitchPin);
  AFMS2.begin();  // create with the default frequency 1.6KHz
  CraneMotor->setSpeed(50);
  while (TeaBallUpSwitchValue !=HIGH){
    TeaBallUpSwitchValue = digitalRead(TeaBallUpSwitchPin);
    CraneMotor->run(FORWARD);
  }
  CraneMotor->setSpeed(0);
  }

void pull_teaball_down(){
  Serial.println("Pulling teaball down");
  TeaBallDownSwitchValue = digitalRead(TeaBallDownSwitchPin);
  AFMS2.begin();  // create with the default frequency 1.6KHz
  CraneMotor->setSpeed(50);
  while (TeaBallDownSwitchValue !=HIGH){
    TeaBallDownSwitchValue = digitalRead(TeaBallDownSwitchPin);
    CraneMotor->run(BACKWARD);
  }
  CraneMotor->setSpeed(0);
  }

void immerge_teaball(){
  Serial.println("Immerging teaball");
  AFMS2.begin();  // create with the default frequency 1.6KHz
  CraneMotor->setSpeed(50);
  CraneMotor->run(BACKWARD);
  delay(up_to_down_time/2);
  CraneMotor->setSpeed(0);
  }

 void rotate_crane(int step_index){
  AFMS2.begin();
  AccelCranestepper.setMaxSpeed(200);
  AccelCranestepper.setAcceleration(30);
  if (step_index==0){
    CraneDestination = CraneHomePosition;
    
  }
  else if (step_index==1){
       Serial.println("yoo");
    CraneDestination = CraneHomePosition - 450;
  }
  else{
    CraneDestination = CraneHomePosition  - 780;
  }
  AccelCranestepper.moveTo(CraneDestination);  
  while (AccelCranestepper.currentPosition() != CraneDestination) {
//   Serial.println("running crane motor");
   AccelCranestepper.runToNewPosition(CraneDestination);
//   Serial.println(AccelCranestepper.currentPosition());
  }
   craneStepper->release();
}
