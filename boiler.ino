 int preheat_temp = 75;
 int ThermoblockRelay1Value;
 int ThermoblockRelay2Value;
 
 void heat_thermoblock(){
   while (thermocouple1.readCelsius() < preheat_temp) {
       turn_thermoblock_on();
       displayTemperature(String(thermocouple1.readCelsius(),1));
       Serial.print("temp = ");
       Serial.print(thermocouple1.readCelsius());
       Serial.println(" degC");
       delay(500);
    }
    turn_thermoblock_off();
    while (preheat_temp < 100000) {
       displayTemperature(String(thermocouple1.readCelsius(),1));
       Serial.print("temp = ");
       Serial.print(thermocouple1.readCelsius());
       Serial.println(" degC");
       delay(500);
    }
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
