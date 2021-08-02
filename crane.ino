void initialize_crane(){
  Serial.println("Intializing crane");
   craneSwitchPinValue = digitalRead(craneSwitchPin);
   Serial.println("coco");
   while (craneSwitchPinValue != HIGH){
     craneSwitchPinValue = digitalRead(craneSwitchPin);
     AccelCranestepper.setMaxSpeed(1000);
     AccelCranestepper.setSpeed(50); 
     AccelCranestepper.runSpeed();
    }
   craneSwitchPressed();
   Serial.println("Crane initialized");
}



void craneSwitchPressed(){
  Serial.println("Stop rotating the crane !!!");
  if (digitalRead(craneSwitchPin) == HIGH){
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
  AFMS2.begin();  // create with the default frequency 1.6KHz
  CraneMotor->setSpeed(50);
  while (TeaBallDownSwitchValue !=HIGH){
    TeaBallDownSwitchValue = digitalRead(TeaBallDownSwitchPin);
    CraneMotor->run(BACKWARD);
  }
  CraneMotor->setSpeed(0);
  }
