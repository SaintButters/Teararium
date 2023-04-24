void displayTemperature(String Temp)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(10, 0);
    display.print("Pre heating");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.setTextSize(1);
    display.setCursor(5, 25);
    display.print("Temp;");
    display.print(Temp);
    display.print(" degC");
    display.setTextSize(2);
    display.display();
}

void displayPouring(String Temp, String flowrate, String volume_poured)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(20, 0);
    display.print("Pouring");
    display.drawFastHLine(0,10,83,BLACK);
    display.setTextSize(1);
    display.setCursor(5, 15);
    display.print("Temp: ");
    display.print(Temp);
    display.print("degC");

    display.setTextSize(1);
    display.setCursor(5, 28);
    display.print("Flow:");
    display.print(flowrate);
    display.print("mL/s");
    
    display.setTextSize(1);
    display.setCursor(5, 40);
    display.print("Volume:");
    display.print(volume_poured);
    display.print("mL");

    display.display();
}

void display_volume_choice(){
    readRotaryEncoder();
    if (up){
      if (waterVolume[TeaSize]<1000){
        waterVolume[TeaSize] = waterVolume[TeaSize] + 5;
        up = false;
      }
    }
    else if (down){
      if (waterVolume[TeaSize]>0){
        waterVolume[TeaSize] = waterVolume[TeaSize] - 5;
        down = false;
      }
    }
    int vol = waterVolume[TeaSize];
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(17, 0);
    display.print("Volume [mL]");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(10, 20);
    display.setTextSize(3);
    display.print(vol);
    display.display();
}

void display_timer(int seconds){
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(10, 0);
    display.print("Infusing...");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(20, 20);
    display.setTextSize(3);
    display.print(seconds);
    display.setTextSize(2);
    display.display();
}

void display_weight(float weight){
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("TEA MASS");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 20);
    display.setTextSize(1);
    display.print(weight);
    display.println(" grams");
    display.display();
}
