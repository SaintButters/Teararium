 int ThermoblockRelayValue;
 
 
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
    ThermoblockRelayValue = digitalRead(Thermoblock_pin);
    delay(250);
    if (ThermoblockRelayValue != HIGH) {
    Serial.println("closing thermoblock relay");
    digitalWrite(Thermoblock_pin, HIGH);
    }
    delay(250);
  }
  

  void turn_thermoblock_off(){
    Serial.println("Turning thermoblock off");
    delay(250);
    Serial.println("opening relay");
    digitalWrite(Thermoblock_pin, LOW);
    delay(250);
  }
