#include <Adafruit_MotorShield.h>


void pour_water(int desired_volume) {
   Serial.println("Start pouring process");
  open_valve();
  pouring_time = 0;
  volume_poured = 0;
  // turn LED on:  

  uint8_t i;
  if (PumpMotorState == 0) {
    open_valve();
    while (volume_poured < desired_volume) {
      flowrate = measure_flowrate();
      step_volume_poured = 0.25 * flowrate;
      run_pump();
      delay(250);
      volume_poured = step_volume_poured + volume_poured;
      Serial.print("Volume = ");
      Serial.print(volume_poured, DEC); 
      Serial.print(" mL");
      Serial.print(" /");
      Serial.print(" desired");
      Serial.println(" mL");
    }
    close_valve();
    delay(2000);
    stop_pump();
  }
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

void run_pump() {
  AFMS3.begin();  // create with the default frequency 1.6KHz
  PumpMotor->setSpeed(125);
  PumpMotor->run(FORWARD);
  PumpMotorState = 1;
}
void stop_pump() {
  AFMS3.begin();  // create with the default frequency 1.6KHz
  PumpMotor->setSpeed(0);
  PumpMotor->run(RELEASE);
  PumpMotorState = 0;
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
      Serial.print("Debit = ");
      Serial.print(mL_per_sec, DEC); // Print litres/hour
      Serial.println(" mL/Sec");
   }
   return mL_per_sec;
}

void flow () // Interrupt function
{
   flow_frequency++;
}
