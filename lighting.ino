
void turn_buttons_leds_on(){
  Serial.println("Turning buttons leds on");
  analogWrite(switchPinled1, 255);
  analogWrite(switchPinled2, 255);
  analogWrite(switchPinled3, 255);
  analogWrite(switchPinled4, 255);
  analogWrite(switchPinled5, 255);
  analogWrite(switchPinled6, 255);
}

void turn_buttons_leds_on_style(){
  Serial.println("Turning buttons leds on with style");
  analogWrite(switchPinled3, 255);
  analogWrite(switchPinled4, 255);
  delay(100);
  analogWrite(switchPinled2, 255);
  analogWrite(switchPinled5, 255);
  delay(100);
  analogWrite(switchPinled6, 255);
  analogWrite(switchPinled1, 255);
}

void turn_buttons_leds_off(){
  Serial.println("Turning buttons leds off");
  analogWrite(switchPinled1, 0);
  analogWrite(switchPinled2, 0);
  analogWrite(switchPinled3, 0);
  analogWrite(switchPinled4, 0);
  analogWrite(switchPinled5, 0);
  analogWrite(switchPinled6, 0);
    }

void turn_buttons_leds_off_preparation(int tea_index){
  if (tea_index==1){
    analogWrite(switchPinled5, 0);
    analogWrite(switchPinled6, 0);
  }
  else if(tea_index==2){
    analogWrite(switchPinled4, 0);
    analogWrite(switchPinled6, 0);
  }
  else if (tea_index==3){
    analogWrite(switchPinled4, 0);
    analogWrite(switchPinled5, 0);
  }
  else if (tea_index==0){
    analogWrite(switchPinled4, 0);
  }
   else if (tea_index==4){
    analogWrite(switchPinled5, 0);
  }
}    

void turn_lights_on(){
  if (leds_enabled == true){
  digitalWrite(ledPin, HIGH);
  }
}

void turn_lights_off(){
  digitalWrite(ledPin, LOW);
}

void turn_fireflies_on(){
  analogWrite(firefliesPin, 140);
}

void turn_fireflies_off(){
  analogWrite(firefliesPin, 0);
}
