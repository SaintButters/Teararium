
void activate_shovel(){
   shovel_servo.attach(11);
   for (pos = 0; pos <=80; pos +=1) {
            shovel_servo.write(pos);
            delay(20);
            }
           for (pos = 80; pos >=0; pos -=1) {
            shovel_servo.write(pos);
            delay(20);
            }
            delay(1000);
    shovel_servo.detach();
    }
     
