// int preheat_temp = 95;
 int preheat_temp = 55;
 int ThermoblockRelay1Value;
 int ThermoblockRelay2Value;
 
 void monitor_thermoblock(){
    displayTemperature(String(computed_temperature(),0));
    Serial.print("Thermoblock temp :");
    Serial.println(String(computed_temperature()));
    delay(500);
    if(computed_temperature()>130){
      Serial.println("Maximum temperature reached ! Abord !");
      turn_thermoblock_off();
    }
  }
  

  void preHeat_thermoblock(){
    Serial.println("Pre heating thermoblock");
    turn_thermoblock_on();
    delay(250);
    while (computed_temperature() < preheat_temp){
      delay(250);
      if (turn_off == true){
        monitor_thermoblock();
        return;
      }
      monitor_thermoblock();
    }
    Serial.println("Pre heating temp reached");
    turn_thermoblock_off();
  }
  
  void turn_thermoblock_on(){
    
    Serial.println("Turning thermoblock on");
    ThermoblockRelay1Value = digitalRead(ThermoblockRelayPin1);
    ThermoblockRelay2Value = digitalRead(ThermoblockRelayPin2);
    delay(500);
    if (ThermoblockRelay1Value != LOW) {
    Serial.println("closing thermoblock relay 1");
    digitalWrite(ThermoblockRelayPin1, LOW);
    }
    delay(500);
    if (ThermoblockRelay2Value != LOW) {
    Serial.println("closing thermoblock relay 2");
    digitalWrite(ThermoblockRelayPin2, LOW);
    }
  }
  

  void turn_thermoblock_off(){
    Serial.println("Turning thermoblock off");
    delay(500);
    Serial.println("opening relay 1");
    digitalWrite(ThermoblockRelayPin1, HIGH);
    delay(500);
    Serial.println("opening relay 2");
    digitalWrite(ThermoblockRelayPin2, HIGH);
  }
