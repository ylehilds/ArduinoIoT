/*
  Explore IoT - Activity 01
 
  Read values from a temperature and humidity sensor
  and print it in Serial Monitor and on a colored display.
 
  This example uses the IoT carrier and the MKR WiFi 1010.
 
  Based on code by
  (c) 2019 D. Cuartielles for Arduino
 
  Written by:
  (c) 2020 K. SÃ¶derby for Arduino
 
  This code is Free Software licensed under GPLv3
*/
 
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
float temperature = 0;
float humidity = 0;
 
void setup() {
  Serial.begin(9600);
  //Wait to open the Serial monitor to start the program and see details on errors
  
 
  //Set if it has the Enclosure mounted
  CARRIER_CASE = true;
  //Initialize the IoTSK carrier and output any errors in the serial monitor
  carrier.begin();
}
 
void loop() {
  // read the sensor values
  temperature = carrier.Env.readTemperature(FAHRENHEIT);
  humidity = carrier.Env.readHumidity();
 
  //Update touch buttons
  carrier.Buttons.update();
 
  // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" Â°F");
 
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
 
  //function to print out values
  if (carrier.Buttons.onTouchDown(TOUCH0)) {
    printTemperature();
  }
 
  if (carrier.Buttons.onTouchDown(TOUCH1)) {
    printHumidity();
  }
}
 
 
void printTemperature() {
  //configuring display, setting background color, text size and text color
  carrier.display.fillScreen(ST77XX_RED); //red background
  carrier.display.setTextColor(ST77XX_WHITE); //white text
  carrier.display.setTextSize(6); //large sized text
 
  carrier.display.setCursor(30, 50); //sets position for printing (x and y)
  carrier.display.print("Temp: ");
  carrier.display.setTextSize(4); //decreasing text size
  carrier.display.setCursor(40, 120); //sets new position for printing (x and y)
  carrier.display.print(temperature);
  carrier.display.print(" F");
}
 
void printHumidity() {
  //configuring display, setting background color, text size and text color
  //if humidity is over 80, we set the display to a red background
  if (humidity >= 80) carrier.display.fillScreen(ST77XX_RED); //red background
  //if humidity is between 60 and 80, we set the display to a yellow background
  else if (humidity >= 60 && humidity <= 79) carrier.display.fillScreen(ST77XX_YELLOW); //yellow background
  //if humidity is between 30 and 60, we set the display to a green background
  else if (humidity >= 30 && humidity <= 59) carrier.display.fillScreen(ST77XX_GREEN); //green background
  //if humidity less than 30, we set the display to a magenta background
  else if (humidity < 30) carrier.display.fillScreen(ST77XX_MAGENTA); //magenta background
  carrier.display.setTextColor(ST77XX_WHITE); //white text
  carrier.display.setTextSize(2); //medium sized text
 
  carrier.display.setCursor(20, 110); //sets position for printing (x and y)
  carrier.display.print("Humi: ");
  carrier.display.print(humidity);
  carrier.display.println(" %");
}