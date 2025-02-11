 int ThermoblockRelay1Value;
 int ThermoblockRelay2Value;
 
 
 void monitor_thermoblock(boolean display_temp){
    if (display_temp == true){
      displayTemperature(String(computed_temperature(),0));
      Serial.print("Thermoblock temp :");
      Serial.println(String(computed_temperature()));
    }
    if(computed_temperature()>200){
      Serial.println("Maximum temperature reached ! Abord !");
      turn_thermoblock_off();
      log_info("Maximum temperature reached ! Preparation aborted !", 1, 0 , 10);
      delay(200);
    }
  }
  

  void preHeat_thermoblock(int tea_index){
    Serial.println("Pre heating thermoblock");
    turn_thermoblock_on();
    delay(250);
    while (computed_temperature() < infusingTemp[tea_index] - 40){
      delay(250);
      if (is_powered()==false){
        turn_thermoblock_off();
        monitor_thermoblock(true);
        return;
      }
      monitor_thermoblock(true);
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
