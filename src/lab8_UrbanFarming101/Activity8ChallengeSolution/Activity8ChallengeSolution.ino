/*
  Sketch generated by the Arduino IoT Cloud Thing "IoTK_Activity_08"
  https://create.arduino.cc/cloud/things/4c178f1c-a581-49bc-8123-4f6d8f21d4b2
 
  Arduino IoT Cloud Properties description
 
  The following variables are automatically generated and updated when changes are made to the Thing properties
 
  String plant_feeling;
  float humidity;
  float light;
  float temperature;
  CloudColoredLight rgbColor;
  int moistValue;
  bool relay_1;
  bool relay_2;
  bool updateDisplay;
 
  Properties which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/
 
#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
int moistPin = A1;
 
String relayState1 = "";
String relayState2 = "";
 
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // Defined in thingProperties.h
  initProperties();
  
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  CARRIER_CASE = true;
  carrier.begin();
  
  setDebugMessageLevel(4);   //Get Cloud Info/errors , 0 (only errors) up to 4
  ArduinoCloud.printDebugInfo();
  
  while (ArduinoCloud.connected() != 1) {
    ArduinoCloud.update();
    carrier.display.setTextSize(3);
    carrier.display.setCursor(20, 70);
    carrier.display.println("Waiting For");
    carrier.display.setCursor(5, 110);
    carrier.display.println("Connection...");
    delay(500);
  }
}
 
void loop() {
  ArduinoCloud.update();
  // Your code here
  //   ArduinoCloud.update();
  // // Your code here
 
  if (relay_1 == true) {
    carrier.Relay1.open();
    relayState1 = "ON";
  }
  else {
    carrier.Relay1.close();
    relayState1 = "OFF";
  }
 
  if (relay_2 == true) {
    carrier.Relay2.open();
    relayState2 = "ON";
  }
  else {
    carrier.Relay2.close();
    relayState2 = "OFF";
  }
 
 
  /* if (carrier.Light.colorAvailable()) {
     int none;//not gonna be used
     carrier.Light.readColor( none,  none,  none , light);
    }*/
  light = 500;
 
  temperature = carrier.Env.readTemperature(FAHRENHEIT);
  humidity = carrier.Env.readHumidity();
 
  int rawMoistValue = analogRead(moistPin);
  moistValue = map(rawMoistValue, 0, 1023, 100, 0);
 
  if (humidity > 60) {
    plant_feeling = "I'm feeling quite humid, I think need a bit of air...";
  }
 
  if (temperature > 25) {
    plant_feeling = "Wow, it's quite warm in here.. could you turn on the Air Conditioning?";
  }
 
  if (moistValue < 10) {
    plant_feeling = "Thirsty...";
  }
 
  if (light < 50) {
    plant_feeling = "Where did everyone go? It's really dark in here..";
  }
 
}
 
 
void onRgbColorChange() {
  // Do something
  uint8_t r, g, b;
  rgbColor.getValue().getRGB(r, g, b);
  if (rgbColor.getSwitch()) {
    carrier.leds.fill((g, r, b), 0, 5);
  }
  else {
    carrier.leds.fill(0, 0, 5);
  }
}
 
 
void onUpdateDisplayChange() {
  // Do something
  carrier.display.fillScreen(ST77XX_WHITE);
  carrier.display.setTextColor(ST77XX_RED);
  carrier.display.setTextSize(2);
 
  carrier.display.setCursor(20, 30);
  carrier.display.print("Temp: ");
  carrier.display.print(temperature);
  carrier.display.print(" F");
 
  carrier.display.setCursor(20, 50);
  carrier.display.print("Humi: ");
  carrier.display.print(humidity);
  carrier.display.print(" %");
 
  carrier.display.setTextColor(ST77XX_ORANGE);
  carrier.display.setCursor(20, 70);
  carrier.display.print("Light: ");
  carrier.display.print(light);
 
  carrier.display.setTextColor(ST77XX_BLUE);
  carrier.display.setCursor(20, 90);
  carrier.display.print("Moist: ");
  carrier.display.print(moistValue);
  carrier.display.print(" %");
 
  carrier.display.setTextColor(ST77XX_BLUE);
  carrier.display.setCursor(20, 120);
  carrier.display.print("R1: ");
  carrier.display.print(relayState1);
 
  carrier.display.print(" R2: ");
  carrier.display.print(relayState2);
 
  updateDisplay = false;
}
 
void onRelay1Change() {
  // Do something
}
 
 
void onRelay2Change() {
  // Do something
}