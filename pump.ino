#include <Adafruit_MotorShield.h>

int incomingByte = 0; // for incoming serial data

void run_pump(int pump_power_pct) {    
  Serial.println("Activating pump");     
  digitalWrite(PumpPin1, HIGH); 
  digitalWrite(PumpPin2, LOW);
  analogWrite(enablePumpPin, pump_power_pct); 
  PumpMotorState = 1;
}

void stop_pump() {       
  Serial.println("Stopping pump");      
  digitalWrite(PumpPin1, LOW); 
  digitalWrite(PumpPin2, LOW);
  PumpMotorState = 0;
}

void pour_water(int tea_index, int tea_size, bool heating, bool preheating) {
  Serial.println("Start pouring process");
  pouring_time = 0;
  volume_poured = 0;
  int heater_timer = 0;
  enough_water = false;
  int abonormal_flowrate_count = 0;
  Serial.print("temp = ");
  Serial.print(String(computed_temperature()));
  Serial.println(" degC");
  Serial.print("Angle servo : ");
  Serial.println(arm_servo.read());
  if (130<arm_servo.read()<140){
      if (preheating == true){
        preHeat_thermoblock(tea_index);
      }
      delay(250);
      run_pump(pump_power_pct);
      if (heating == true){
        turn_thermoblock_on();
      }
      Serial.print("Volume = ");
      Serial.print(volume_poured); 
      Serial.println(" mL");
      Serial.print("Volume to pour = ");
      Serial.print(waterVolume[tea_size]);
      Serial.println(" mL");
      while (volume_poured < waterVolume[tea_size]) {
        Serial.println("Starting pouring");
        if (is_powered()==false){
          turn_thermoblock_off();
          stop_pump();
          return;
        }
        Serial.print("temp thblk= ");
        Serial.print(String(computed_temperature()));
        Serial.println(" degC");
        if (computed_temperature()<5 or computed_temperature()>150){
          Serial.print("Thermoblock temp out of allowed range");
          turn_thermoblock_off();
          stop_pump();
          return;
        }
        monitor_thermoblock(false);
        flowrate = measure_flowrate();
        step_volume_poured = 0.165 * flowrate; // tested value
        volume_poured = step_volume_poured + volume_poured;
        Serial.print("Debit = ");
        Serial.print(mL_per_sec); // Print litres/hour
        Serial.println(" mL/Sec");
        Serial.print("Volume = ");
        Serial.print(volume_poured); 
        Serial.println(" mL");
        Serial.print("temp thblk= ");
        Serial.print(String(computed_temperature()));
        Serial.println(" degC");
        displayPouring(String(computed_temperature(),0),String(flowrate,0),String(volume_poured,0));
        if (flowrate < 5){
          abonormal_flowrate_count = abonormal_flowrate_count + 1;
          Serial.print(abonormal_flowrate_count);
        }
        else{
          abonormal_flowrate_count = 0;
        }
        if (abonormal_flowrate_count > 8){
          Serial.print("Water flow too low. Filling ended");
          log_info("Water flow too low. Filling ended", 1, 0 , 10);
          turn_thermoblock_off();
          stop_pump();
          delay(6000);
          break;
        }
        if (heater_timer > 120){
          Serial.print("Preheating stoppped : timer ended");
          log_info("Preheating stoppped : timer ended", 1, 0 , 10);
          turn_thermoblock_off();
          stop_pump();
          delay(6000);
          break;
        }
        delay(250);
        heater_timer = heater_timer+1;
      }
      delay(250);
      turn_thermoblock_off();
      delay(250);
//      stop_pump();
      if (volume_poured > 0.66 * waterVolume[tea_size]){
          enough_water = true;
          stop_pump();
        }
       else{
         stop_pump();
         enough_water = false;
       }
    }
  }


float measure_flowrate () {
  currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      L_per_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      mL_per_sec = L_per_hour * 1000 / 3600;
      flow_frequency = 0; // Reset Counter
//      Serial.print("flow_frequency:");
//      Serial.println(flow_frequency);
//      Serial.print("L_per_hour:");
//      Serial.println(L_per_hour);
//      Serial.print("Debit = ");
//      Serial.print(mL_per_sec); // Print litres/hour
//      Serial.println(" mL/Sec");
      
   }
   return mL_per_sec;
}

void flow () // Interrupt function
{
   flow_frequency++;
}
