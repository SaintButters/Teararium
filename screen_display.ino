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

void displayWeight(String weight)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.print("Tea Weight");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.setTextSize(1);
    display.setCursor(5, 25);
    display.print(weight);
    display.print(" grams");
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
