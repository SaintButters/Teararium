
void activate_shovel(){
   Serial.println("Activating shovel");
   shovel_servo.attach(11);

   for (pos = 0; pos <=80; pos +=1) {
            shovel_servo.write(pos);
            delay(10);
            }
            delay(1000);
           for (pos = 80; pos >=0; pos -=1) {
            shovel_servo.write(pos);
            delay(10);
            }
            delay(1000);
    shovel_servo.detach();
    }
     
