void displayTemperature(String Temp)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.print("Temeperature");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.setTextSize(1);
    display.setCursor(5, 25);
    display.print(Temp);
    display.print(" degC");
    display.setTextSize(2);
    display.display();
}
