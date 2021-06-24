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
int ambiance_line = 27;
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
int read_setting(int setting_index){

setting_value = 0;
line_counter = 0;
//Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
Serial.print("Initializing SD card...");
if (!SD.begin(10)) {
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
return setting_value;
}


int get_setting(int menuItem, int  teaItem, int soundItem, int lightingItem) {
//  Serial.begin(9600);
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
    setting = ambiance;
  }
  else if (menuItem==5 and lightingItem==2){
    setting = selectedOnOff;
  }
  return setting.toInt();
}

int get_setting_line(int menuItem, int  teaItem, int soundItem, int lightingItem) {
//  Serial.begin(9600);
  Serial.println(" menuItem " + menuItem);
  Serial.println(" teaItem " + teaItem);
  Serial.println(" soundItem " + soundItem);
  Serial.println(" lightingItem " + lightingItem);
  line = "";
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
    line = ambiance_line;
  }
  else if (menuItem==5 and lightingItem==2){
    line = backlight_line;
  }
  return line;
}
