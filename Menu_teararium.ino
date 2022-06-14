   //////////////////////////////////////////////
  //  Teararium Rotary Encoder Menu by Sam    //
 //                 v1.0                     //
//   Inspired by http://www.educ8s.tv       //
/////////////////////////////////////////////

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
int menuItem = 1;
int teaItem = 1;
int soundItem = 1;
int lightingItem = 1;
int frame = 1;
int page = 1;
int lastMenuItem = 1;
int lastTeaItem = 1;
int lastSoundItem = 1;
int lastLightingItem = 1;

String menuItem1 = "Tea 1";
String menuItem2 = "Tea 2";
String menuItem3 = "Tea 3";
String menuItem4 = "Sound";
String menuItem5 = "Lighting";
String menuItem6 = "Reset";

String teaItem1 = "Temperature";
String teaItem2 = "Infusing time";
String teaItem3 = "Back";
String soundItem1 = "Theme";
String soundItem2 = "Volume";
String soundItem3 = "Back";
String lightingItem1 = "Leds";
String lightingItem2 = "Display";
String lightingItem3 = "Back";

String tea = "";
String unit ="";

String theme[4] = { "Random", "LOTR", "Witcher", "Jules sucks   LoL" };
int themeCount = 4;
int selectedTheme = 0;
String onOff[2] = { "On", "Off"};
int backLightSelectedOnOff = 0;
int ledSelectedOnOff = 0;

boolean sound = true;
boolean backlight = true;
int contrast=60;
int volume = 50;
boolean up = false;
boolean down = false;
boolean middle = false;
boolean lastMenu = false;
ClickEncoder *encoder;
int16_t last, value;
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 5, 4, 3); //Download the latest Adafruit Library in order to use this constructor

void setupMenu(){
  pinMode(7,OUTPUT);
  turnBacklightOn();
  
  encoder = new ClickEncoder(A8, A9, A10);
  encoder->setAccelerationEnabled(false);
   
  display.begin();      
  display.clearDisplay(); 
  setContrast();  

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  
  last = encoder->getValue();
}
  
void displayMenu() {
  drawMenu();
  if (backLightSelectedOnOff == 0) {
    turnBacklightOn();
  }
  else{
    turnBacklightOff();
  }
  if (ledSelectedOnOff == 0) {
    if (powered == true){
    enable_leds();
    }
  }
  else{
    disable_leds();
  }
  readRotaryEncoder();

   ClickEncoder::Button b = encoder->getButton();
   if (b != ClickEncoder::Open) {
   switch (b) {
      case ClickEncoder::Clicked:
         middle=true;
        break;
    }
  }    
  
  if (up && page ==1 ) {
     
    up = false;
    if(menuItem==2 && frame ==2)
    {
      frame--;
    }

     if(menuItem==4 && frame ==4)
    {
      frame--;
    }
      if(menuItem==3 && frame ==3)
    {
      frame--;
    }
    lastMenuItem = menuItem;
    menuItem--;
    if (menuItem==0)
    {
      menuItem=1;
    } 
  }
    if (up && page ==2 && menuItem<=3 ) {
    Serial.print("UP");
    up = false;
    teaItem--;
    if (teaItem==0)
    {
      teaItem=1;
    } 
  }
     if (up && page ==2 && menuItem ==4 ) {
    Serial.print("UP");
    up = false;
    soundItem--;
    if (soundItem==0)
    {
      soundItem=1;
    } 
   }
  
  if (up && page ==2 && menuItem ==5 ) {
    Serial.print("UP");
    up = false;
    lightingItem--;
    if (lightingItem==0)
    {
      lightingItem=1;
    } 
  }

  if (up && page == 3  && menuItem ==1 ) {
    
    up = false;
    if (teaItem ==1){
    temp1--;
  }
    else if (teaItem ==2){
    time1--;
    }
  }
  if (up && page == 3  && menuItem ==2 ) {
    up = false;
    if (teaItem ==1){
    temp2--;
  }
    else if (teaItem ==2){
    time2--;
    }
  }
  if (up && page == 3  && menuItem ==3 ) {
    up = false;
    if (teaItem ==1){
    temp3--;
  }
    else if (teaItem ==2){
    time3--;
    }
  }
  if (up && page == 3  && menuItem ==4 ) {
    up = false;
    if (soundItem ==2){
    volume--;
    }
    else if (soundItem ==1){
    selectedTheme--;
    if(selectedTheme == -1)
    {
      selectedTheme = themeCount -1;
    }
    }
  }
  
   if (up && page == 3  && menuItem ==5 ) {
    up = false;
    if (lightingItem ==1){
    ledSelectedOnOff--;
    if(ledSelectedOnOff == -1)
    {
      ledSelectedOnOff = 1;
    }
  }
   else if (lightingItem ==2){
    backLightSelectedOnOff--;
    if(backLightSelectedOnOff == -1)
    {
      backLightSelectedOnOff = 1;
    }
    }
  }
  
  if (down && page ==1) //We have turned the Rotary Encoder Clockwise
  {

    down = false;
    if(menuItem==3 && lastMenuItem == 2)
    {
      frame ++;
    }else  if(menuItem==4 && lastMenuItem == 3)
    {
      frame ++;
    }
     else  if(menuItem==5 && lastMenuItem == 4 && frame!=4)
    {
      frame ++;
    }
    lastMenuItem = menuItem;
    menuItem++;  
    if (menuItem==7) 
    {
      menuItem--;
    }
  }

    if (down && page ==2 && menuItem<=3 ) {
    down = false;
    teaItem++;
     if (teaItem==4) 
    {
      teaItem--;
    }
    }
    if (down && page ==2 && menuItem == 4 ) {
    down = false;
    soundItem++;
     if (soundItem==4) 
    {
      soundItem--;
    }
  }
    if (down && page ==2 && menuItem == 5 ) {
    down = false;
    lightingItem++;
     if (lightingItem==4) 
    {
      lightingItem--;
    }
  }

  if (down && page == 3  && menuItem ==1 ) {
    down = false;
    if (teaItem ==1){
    temp1++;
  }
    else if (teaItem ==2){
    time1++;
    }
    }
      if (down && page == 3  && menuItem ==2 ) {
        down = false;
    if (teaItem ==1){
    temp2++;
  }
    else if (teaItem ==2){
    time2++;
    }
  }
  if (down && page == 3  && menuItem ==3 ) {
    down = false;
    if (teaItem ==1){
    temp3++;
  }
    else if (teaItem ==2){
    time3++;
    }
  }
  if (down && page == 3  && menuItem ==4 ) {
    down = false;
    if (soundItem ==2){
    volume++;
  }
  else if (soundItem ==1){
    selectedTheme++;
    if(selectedTheme == themeCount)
    {
      selectedTheme = 0;
    }
    }
  }
  if (down && page == 3  && menuItem ==5 ) {
    down = false;
    if (lightingItem ==1){
    ledSelectedOnOff++;
    if(ledSelectedOnOff == 2)
    {
      ledSelectedOnOff = 0;
    }
    }
    else if (lightingItem ==2){
    backLightSelectedOnOff++;
    if(backLightSelectedOnOff == 2)
    {
      backLightSelectedOnOff = 0;
    }
    }
  }
  
  
  
  
  if (middle) //Middle Button is Pressed
  {
    middle = false;
    if (page == 1) {
     Serial.print("go to page 2");
     teaItem = 1;
     soundItem = 1;
     page=2;
     
     }
     else if (page == 2) {
       if (teaItem!=3 and soundItem!=3 and lightingItem !=3)
       {
        Serial.print("go to page 3");
        page=3; 
       }
     }
     if (teaItem==3 or soundItem==3 or lightingItem ==3){
       if (page == 2) {
        page = 1;
        frame = 1;
        menuItem = 1;
        teaItem = 1;
        soundItem = 1;
        lightingItem = 1;
        Serial.print("go back to page 1");
       }
      }
     if (page ==3 && lastMenu ==true){
    page = 2;
    update_setting(menuItem, teaItem, soundItem, lightingItem);
    lastMenu = false;
    }
  }
  if (page == 3){
    lastMenu = true;
  }
}

  void drawMenu()
  {
  if (page==1) 
  {    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("TEARARIUM");
    display.drawFastHLine(0,10,83,BLACK);

    if(menuItem==1 && frame ==1)
    {   
      displayMenuItem(menuItem1, 15,true);
      displayMenuItem(menuItem2, 25,false);
      displayMenuItem(menuItem3, 35,false);
    }
    else if(menuItem == 2 && frame == 1)
    {
      displayMenuItem(menuItem1, 15,false);
      displayMenuItem(menuItem2, 25,true);
      displayMenuItem(menuItem3, 35,false);
    }
    else if(menuItem == 3 && frame == 1)
    {
      displayMenuItem(menuItem1, 15,false);
      displayMenuItem(menuItem2, 25,false);
      displayMenuItem(menuItem3, 35,true);
    }
     else if(menuItem == 4 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,false);
      displayMenuItem(menuItem3, 25,false);
      displayMenuItem(menuItem4, 35,true);
    }

      else if(menuItem == 3 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,false);
      displayMenuItem(menuItem3, 25,true);
      displayMenuItem(menuItem4, 35,false);
    }
    else if(menuItem == 2 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,true);
      displayMenuItem(menuItem3, 25,false);
      displayMenuItem(menuItem4, 35,false);
    }
    
    else if(menuItem == 5 && frame == 3)
    {
      displayMenuItem(menuItem3, 15,false);
      displayMenuItem(menuItem4, 25,false);
      displayMenuItem(menuItem5, 35,true);
    }

    else if(menuItem == 6 && frame == 4)
    {
      displayMenuItem(menuItem4, 15,false);
      displayMenuItem(menuItem5, 25,false);
      displayMenuItem(menuItem6, 35,true);
    }
    
      else if(menuItem == 5 && frame == 4)
    {
      displayMenuItem(menuItem4, 15,false);
      displayMenuItem(menuItem5, 25,true);
      displayMenuItem(menuItem6, 35,false);
    }
      else if(menuItem == 4 && frame == 4)
    {
      displayMenuItem(menuItem4, 15,true);
      displayMenuItem(menuItem5, 25,false);
      displayMenuItem(menuItem6, 35,false);
    }
    else if(menuItem == 3 && frame == 3)
    {
      displayMenuItem(menuItem3, 15,true);
      displayMenuItem(menuItem4, 25,false);
      displayMenuItem(menuItem5, 35,false);
    }
        else if(menuItem == 2 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,true);
      displayMenuItem(menuItem3, 25,false);
      displayMenuItem(menuItem4, 35,false);
    }
    else if(menuItem == 4 && frame == 3)
    {
      displayMenuItem(menuItem3, 15,false);
      displayMenuItem(menuItem4, 25,true);
      displayMenuItem(menuItem5, 35,false);
    }   
  }
    else if (page==2) 
    {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(25, 0);
    display.drawFastHLine(0,10,83,BLACK);

    if(menuItem<=3)
    {   
      display.print("Tea ");
      display.println(menuItem);
      if(teaItem ==1){
      displayMenuItem(teaItem1, 15,true);
      displayMenuItem(teaItem2, 25,false);
      displayMenuItem(teaItem3, 35,false);
    }
      else if(teaItem == 2){
      displayMenuItem(teaItem1, 15,false);
      displayMenuItem(teaItem2, 25,true);
      displayMenuItem(teaItem3, 35,false);
    }
      else if(teaItem == 3){
      displayMenuItem(teaItem1, 15,false);
      displayMenuItem(teaItem2, 25,false);
      displayMenuItem(teaItem3, 35,true);
    }
    }
    if(menuItem==4)
    {   
      display.print("Sound");
      if(soundItem ==1){
      displayMenuItem(soundItem1, 15,true);
      displayMenuItem(soundItem2, 25,false);
      displayMenuItem(soundItem3, 35,false);
    }
      else if(soundItem == 2){
      displayMenuItem(soundItem1, 15,false);
      displayMenuItem(soundItem2, 25,true);
      displayMenuItem(soundItem3, 35,false);
    }
      else if(soundItem == 3){
      displayMenuItem(soundItem1, 15,false);
      displayMenuItem(soundItem2, 25,false);
      displayMenuItem(soundItem3, 35,true);
    }
    }
     if(menuItem==5)
    {   
      display.setCursor(18, 0);
      display.print("Lighting");
      if(lightingItem ==1){
      displayMenuItem(lightingItem1, 15,true);
      displayMenuItem(lightingItem2, 25,false);
      displayMenuItem(lightingItem3, 35,false);
    }
      else if(lightingItem == 2){
      displayMenuItem(lightingItem1, 15,false);
      displayMenuItem(lightingItem2, 25,true);
      displayMenuItem(lightingItem3, 35,false);
    }
      else if(lightingItem == 3){
      displayMenuItem(lightingItem1, 15,false);
      displayMenuItem(lightingItem2, 25,false);
      displayMenuItem(lightingItem3, 35,true);
    }
    }
    }
    else if (page == 3) {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.drawFastHLine(0,10,83,BLACK);

    if (menuItem == 1 && teaItem == 1){
    displayIntMenuPage(teaItem1, temp1, "degC");
    }
    if (menuItem == 2 && teaItem == 1){
    displayIntMenuPage(teaItem1, temp2, "degC");
    }
    if (menuItem == 3 && teaItem == 1){
    displayIntMenuPage(teaItem1, temp3, "degC");
    }
     if (menuItem == 1 && teaItem == 2){
    displayIntMenuPage(teaItem2, time1, "min");
    }
    if (menuItem == 2 && teaItem == 2){
    displayIntMenuPage(teaItem2, time2, "min");
    }
    if (menuItem == 3 && teaItem == 2){
    displayIntMenuPage(teaItem2, time3, "min");
    }
    if (menuItem == 4 && soundItem == 1){
    displayStringMenuPage(soundItem1, theme[selectedTheme]);
    }
    if (menuItem == 4 && soundItem == 2){
    displayIntMenuPage(soundItem2, volume, "%");
    }
    if (menuItem == 5 && lightingItem == 1){
    displayStringMenuPage(lightingItem1, onOff[ledSelectedOnOff]);
    }
    if (menuItem == 5 && lightingItem == 2){
    displayStringMenuPage(lightingItem2, onOff[backLightSelectedOnOff]);
    }
    }

  display.display();
  }
  

  
  void setContrast()
  {
    display.setContrast(contrast);
    display.display();
  }

  void turnBacklightOn()
  {
    digitalWrite(7,HIGH);
  }

    void turnBacklightOff()
  {
    digitalWrite(7,LOW);
  }

   void enable_leds()
  {
    leds_enabled = true;
    turn_lights_on();
    turn_fireflies_on();
  }

  void disable_leds()
  {
    leds_enabled = false;
    turn_lights_off();
    turn_fireflies_off();
  }
  
  void timerIsr() {
  encoder->service();
}

void displayIntMenuPage(String menuItem, int value, String unit)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.print(menuItem);
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.print("Value ");
    display.print("[" + unit + "]");
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(value);
    display.setTextSize(2);
    display.display();
}

void displayStringMenuPage(String menuItem, String value)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(20, 0);
    display.print(menuItem);
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.setTextSize(1);
    display.setCursor(5, 25);
    display.print(value);
    display.setTextSize(2);
    display.display();
}

void displayMenuItem(String item, int position, boolean selected)
{
    if(selected)
    {
      display.setTextColor(WHITE, BLACK);
    }else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, position);
    display.print(">"+item);
}

void readRotaryEncoder()
{
  value += encoder->getValue();
  
  if (value/2 > last) {
    last = value/2;
    down = true;
    delay(150);
  }else   if (value/2 < last) {
    last = value/2;
    up = true;
    delay(150);
  }
}
