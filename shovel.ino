
void activate_shovel(){
   Serial.println("Activating shovel");
   shovel_servo.write(0);
   shovel_servo.attach(10);
   for (pos = 0; pos <=95; pos +=1) {
            shovel_servo.write(pos);
            delay(10);
            }
            delay(1500);
           for (pos = 95; pos >=0; pos -=1) {
            shovel_servo.write(pos);
            delay(10);
            }
            delay(1000);
    shovel_servo.detach();
    }
     
