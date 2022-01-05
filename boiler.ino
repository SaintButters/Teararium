// int preheat_temp = 95;
 int preheat_temp = 40;
 int ThermoblockRelay1Value;
 int ThermoblockRelay2Value;
 
 void heat_thermoblock(){
   Serial.println(String(computed_temperature()));
    while (computed_temperature() < preheat_temp) {
      turn_thermoblock_on();
      displayTemperature(String(computed_temperature(),1));
      Serial.print("temp = ");
      Serial.print(String(computed_temperature()));
      Serial.println(" degC");
      delay(500);
  }
    turn_thermoblock_off();
//    while (computed_temperature() < 100000) {
//      displayTemperature(String(computed_temperature(),1));
//      Serial.print("temp = ");
//      Serial.print(String(computed_temperature()));
//      Serial.println(" degC");
//      delay(500);
//    }
 }
  
  void turn_thermoblock_on(){
    
    ThermoblockRelay1Value = digitalRead(ThermoblockRelayPin1);
//    Serial.print("ThermoblockRelay1Value is ");
//    Serial.println(ThermoblockRelay1Value);
    ThermoblockRelay2Value = digitalRead(ThermoblockRelayPin2);
//    Serial.print("ThermoblockRelay2Value is ");
//    Serial.println(ThermoblockRelay2Value);
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
