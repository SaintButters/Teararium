void log_info(String message, int text_size, int cursor_x, int cursor_y){
  Serial.println("Start Tea1 preparation");
  display.setTextSize(text_size);
  display.clearDisplay();
  display.setCursor(cursor_x, cursor_y);
  display.print(message);
  display.display();
  Serial.println("End");

}
