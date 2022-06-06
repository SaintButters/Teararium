#include <SPI.h>
#include <SD.h>

int tea1_temp_line = 6;
int tea1_infusion_time_line = 8;
int tea2_temp_line = 10;
int tea2_infusion_time_line = 12;
int tea3_temp_line = 14;
int tea3_infusion_time_line = 16;
int current_tea_line = 18;
int reuse_count_line = 20;
int seconds_since_last_tea_line = 22;
int led_line = 27;
int lullabies_line = 29;
int backlight_line = 31;
int theme_line = 36;
int volume_line = 38;
String file_txt;
String setting;

File myFile;
int line_counter = 0;
String line_buffer;
int setting_value;
int line;

void load_all_settings(){
  Serial.println("Loading settings");
  temp1 = read_setting(tea1_temp_line);
  Serial.println(temp1);
  temp2 = read_setting(tea2_temp_line);
  Serial.println(temp1);
  temp3 = read_setting(tea3_temp_line);
  Serial.println(temp1);
  time1 = read_setting(tea1_infusion_time_line);
  time2 = read_setting(tea2_infusion_time_line);
  time3 = read_setting(tea3_infusion_time_line);
  infusingTemp[0] = 90;
  infusingTemp[1] = temp1;
  infusingTemp[2] = temp2;
  infusingTemp[3] = temp3;
  infusingTime[0] = 320;
  infusingTime[1] = time1*60;
  infusingTime[2] = time2*60;
  infusingTime[3] = time3*60;
  Serial.println("Settings loaded");
}

int read_setting(int setting_index){
  setting_value = 0;
  line_counter = 0;
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(53)) {
  Serial.println("initialization failed!");
  while (1);
  }
  Serial.println("initialization done.");
  // open the file for reading:
  myFile = SD.open("settings.txt");
  if (myFile) {
  // read from the file until there's nothing else in it:
  while (myFile.available()) {
      line_buffer = myFile.readStringUntil(';');
      line_counter +=1;
      if (line_counter==setting_index){
      setting_value=line_buffer.toInt();
      }
  //    Serial.write(myFile.read());
      //do some action here
    }
    myFile.close();
  }
  // close the file:
  
  else {
  // if the file didn't open, print an error:
  Serial.println("error opening settings.txt");
  }
  return int(setting_value);
}


int get_setting(int menuItem, int  teaItem, int soundItem, int lightingItem) {

  Serial.println("menuItem " + menuItem);
  Serial.println("teaItem " + teaItem);
  Serial.println("soundItem " + soundItem);
  Serial.println("lightingItem " + lightingItem);
  setting = "";
  if (menuItem==1 and teaItem==1){
    setting = temp1;
  }
  else if (menuItem==1 and teaItem==2){
    setting = time1;
  }
  else if (menuItem==2 and teaItem==1){
    setting = temp2;
  }
  else if (menuItem==2 and teaItem==2){
    setting = time2;
  }
  else if (menuItem==3 and teaItem==1){
    setting = temp3;
  }
  else if (menuItem==3 and teaItem==2){
    setting = time3;
  }
  else if (menuItem==4 and soundItem==1){
    setting = selectedTheme;
  }
  else if (menuItem==4 and soundItem==2){
    setting = volume;
  }
  else if (menuItem==5 and lightingItem==1){
    setting = ledSelectedOnOff;
  }
  else if (menuItem==5 and lightingItem==2){
    setting = backLightSelectedOnOff;
  }
  return setting.toInt();
}

int get_setting_line(int menuItem, int  teaItem, int soundItem, int lightingItem) {

  Serial.println(" menuItem " + menuItem);
  Serial.println(" teaItem " + teaItem);
  Serial.println(" soundItem " + soundItem);
  Serial.println(" lightingItem " + lightingItem);
  if (menuItem==1 and teaItem==1){
    line = tea1_temp_line;
  }
  else if (menuItem==1 and teaItem==2){
    line = tea1_infusion_time_line;
  }
  else if (menuItem==2 and teaItem==1){
    line = tea2_temp_line;
  }
  else if (menuItem==2 and teaItem==2){
    line = tea2_infusion_time_line;
  }
  else if (menuItem==3 and teaItem==1){
    line = tea3_temp_line;
  }
  else if (menuItem==3 and teaItem==2){
    line = tea3_infusion_time_line;
  }
  else if (menuItem==4 and soundItem==1){
    line = theme_line;
  }
  else if (menuItem==4 and soundItem==2){
    line = volume_line;
  }
  else if (menuItem==5 and lightingItem==1){
    line = led_line;
  }
  else if (menuItem==5 and lightingItem==2){
    line = backlight_line;
  }
  return line;
}
