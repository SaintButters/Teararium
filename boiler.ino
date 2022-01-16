// int preheat_temp = 95;
 int preheat_temp = 80;
 int ThermoblockRelay1Value;
 int ThermoblockRelay2Value;
 
 void monitor_thermoblock(){
    displayTemperature(String(computed_temperature(),0));
    delay(500);
    if(computed_temperature()>130)
    {turn_thermoblock_off();
    }
  }
  

  void preHeat_thermoblock(){
    Serial.print("Pre heating thermoblock");
    turn_thermoblock_on();
    while (computed_temperature() < preheat_temp){
      monitor_thermoblock();
    }
    turn_thermoblock_off();
  }
  
  void turn_thermoblock_on(){

    Serial.println("Turning thermoblock on");
    ThermoblockRelay1Value = digitalRead(ThermoblockRelayPin1);
    ThermoblockRelay2Value = digitalRead(ThermoblockRelayPin2);
    if (ThermoblockRelay1Value != LOW) {
    Serial.println("closing thermoblock relay 1");
    digitalWrite(ThermoblockRelayPin1, LOW);
    }
    if (ThermoblockRelay2Value != LOW) {
    Serial.println("closing thermoblock relay 2");
    digitalWrite(ThermoblockRelayPin2, LOW);
    }
  }
  

  void turn_thermoblock_off(){
    Serial.println("Turning thermoblock off");
    Serial.println("opening relay 1");
    digitalWrite(ThermoblockRelayPin1, HIGH);
    Serial.println("opening relay 2");
    digitalWrite(ThermoblockRelayPin2, HIGH);
  }
