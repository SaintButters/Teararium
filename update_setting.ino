#include <SPI.h>
#include <SD.h>
String buffer;
String file_buffer[41];
String line_buffer2;
String data;
int line_cout;
int value_line;

void save_setting(int data_line, int data_value){

while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
Serial.println("Initializing SD card...");
if (!SD.begin(53)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");
// open the file for reading:
myFile = SD.open("settings.txt");
if (myFile) {
  line_cout = 0;
// read from the file until there's nothing else in it:
while (myFile.available()) {
  line_buffer2 = myFile.readStringUntil(';');
  file_buffer[line_cout]=line_buffer2;
  line_cout +=1;
}
// close the file:
  myFile.close();
}
else {
// if the file didn't open, print an error:
Serial.println("error opening settings.txt");
}

SD.remove("settings.txt");
myFile = SD.open("settings.txt", FILE_WRITE);
// if the file opened okay, write to it:
if (myFile) {
Serial.println("Writing to settings.txt...");
for (int i = 0; i <= line_cout; i++) {
  if (i == data_line-1){
    data = String(data_value);
    data = '\n' + data+ ';';
  }
  else {
    data = file_buffer[i];
    if (i == line_cout) {
      data = data;
    }
    else{
    data = data+';';
    }
    }
    myFile.print(data);
  }
  myFile.close();
  }

// close the file:

else {
// if the file didn't open, print an error:
Serial.println("error opening settings.txt");
}
Serial.println("Setting saved.");
}

void update_setting(int menuItem, int  teaItem, int soundItem, int lightingItem){
  value = get_setting(menuItem, teaItem, soundItem, lightingItem);
  value_line = get_setting_line(menuItem, teaItem, soundItem, lightingItem);
  save_setting(value_line, value);
}
