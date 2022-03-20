#include <Adafruit_MotorShield.h>

int incomingByte = 0; // for incoming serial data

void run_pump(int power) {    
  Serial.println("Activating pump");     
  analogWrite(Pin1, 0);
  analogWrite(Pin2, power);
  PumpMotorState = 1;
}

void stop_pump() {       
  Serial.println("Stopping pump");      
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  PumpMotorState = 0;
}

void pour_water(int desired_volume, bool heating, bool preheating) {
   Serial.println("Start pouring process");
  pouring_time = 0;
  volume_poured = 0;
  // turn LED on:  
  Serial.print("temp = ");
  Serial.print(String(computed_temperature()));
  Serial.println(" degC");
  Serial.print("Angle servo : ");
  Serial.println(arm_servo.read());
  if (130<arm_servo.read()<140){
    if (PumpMotorState == 0) {
      if (preheating == true){
        preHeat_thermoblock();
      }
      delay(500);
      close_vent_valve();
      delay(1000);
      open_valve();
      delay(1000);
      run_pump(220);
      if (heating == true){
        turn_thermoblock_on();
      }
      while (volume_poured < desired_volume) {
        if (turn_off == true){
          turn_thermoblock_off();
          return;
        }
        flowrate = measure_flowrate();
        step_volume_poured = 0.180 * flowrate;
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
      }
      delay(1000);
      turn_thermoblock_off();
      delay(1000);
      close_valve();
      delay(1000);
      purge_pipes();
    }
  }
}

void purge_pipes(){
  open_vent_valve();
  run_pump(150);
  delay(500);
  close_vent_valve();
  stop_pump();
}

void open_valve(){
  Serial.println("Opening valve");
  digitalWrite(solenoidRelayPin, LOW
  );
}
void close_valve(){
  Serial.println("Closing valve");
  digitalWrite(solenoidRelayPin, HIGH);
}

void open_vent_valve(){
  Serial.println("Opening vent valve");
  digitalWrite(solenoid2RelayPin, LOW
  );
}
void close_vent_valve(){
  Serial.println("Closing vent valve");
  digitalWrite(solenoid2RelayPin, HIGH);
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
