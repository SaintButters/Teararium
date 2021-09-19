void displayTemperature(String Temp)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.print("Temperature");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.setTextSize(1);
    display.setCursor(5, 25);
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
    display.print(" G");
    display.setTextSize(2);
    display.display();
}
