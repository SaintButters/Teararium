

void initialize_steppers() {
    SPI.begin();
    while(!Serial);
    
    Serial.println("Initializing crane stepper");
    craneDriver.begin();             // Initiate pins and registeries
    craneDriver.rms_current(600);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
//    driver.en_pwm_mode(1);      // Enable extremely quiet stepping, not available for TMC2208
    craneDriver.pwm_autoscale(1);
    craneDriver.microsteps(32);
    
    craneStepper.setMaxSpeed(2*steps_per_mm); 
//    craneStepper.setAcceleration(0.5*steps_per_mm); 
    craneStepper.setAcceleration(1*steps_per_mm); 
    craneStepper.setEnablePin(EN_PIN_craneStepper);
    craneStepper.setPinsInverted(false, false, true);
    craneStepper.enableOutputs();

    Serial.println("Initializing wagon stepper");
    wagonDriver.begin();             // Initiate pins and registeries
    wagonDriver.rms_current(600);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
//    driver.en_pwm_mode(1);      // Enable extremely quiet stepping, not available for TMC2208
    wagonDriver.pwm_autoscale(1);
    wagonDriver.microsteps(16);
    
    wagonStepper.setMaxSpeed(400*steps_per_mm); 
    wagonStepper.setAcceleration(20*steps_per_mm); 
    wagonStepper.setEnablePin(EN_PIN_wagonStepper);
    wagonStepper.setPinsInverted(false, false, true);
    wagonStepper.enableOutputs();
}
