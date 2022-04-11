/*
  Explore IoT kit - Activity 03 - Challenge
 
  Read information from the all of the sensors
  on the IoT carrier and store it on a
  CSV file inside an SD card. Connect the SD
  card to the slot on the IoT carrier. The amount
  of measurements taken will also be printed on
  the IoT carrier's display.
 
  This code also allows the user to toggle between a
  counting and a non counting state, by using capacitive
  button 1 and 5.
 
  This example uses the MKR IoT carrier and the MKR WiFi 1010.
 
  Based on code by:
  (c) 2019 D. Cuartielles for Arduino
 
  Written by:
  (c) 2020 K. SÃ¶derby for Arduino
 
  This code is Free Software licensed under GPLv3
*/
 
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
//This boolean is used to toggle between "counting" and "not counting" mode
bool counting_mode = false;
 
// variables
float temperature = 0;
float humidity = 0;
float pressure = 0;
int light = 0;
int r, g, b;
 
// gyroscope
float Gx, Gy, Gz;
 
//accelerometer
float Ax, Ay, Az;
 
//track how many measurements have been made
int counter = 0;
 
void setup() {
  Serial.begin(9600);
 
  //Initialize the IoTSK carrier and output any errors in the serial monitor
  CARRIER_CASE = true;
  carrier.begin();
  
  // init the CSV file with headers
  Serial.println("temperature,humidity,pressure,light,Ax,Ay,Az,Gx,Gy,Gz");
}
 
void loop() {

 
  carrier.Buttons.update();
 
  // read the sensors values
  temperature = carrier.Env.readTemperature(FAHRENHEIT);
  humidity = carrier.Env.readHumidity();
  pressure = carrier.Pressure.readPressure();
 
  while (!carrier.Light.colorAvailable()) {
    delay(5);
  }
  carrier.Light.readColor(r, g, b, light);
 
  // read the IMU values
  carrier.IMUmodule.readAcceleration(Ax, Ay, Az);
  carrier.IMUmodule.readGyroscope(Gx, Gy, Gz);
 
 
  //If we press button 0, counting_mode changes to true
 
  if (carrier.Button0.onTouchDown()) {
    counting_mode = true;
    delay(500);
  }
 
  //If we press button 4, counting_mode changes to false
  if (carrier.Button4.onTouchDown()) {
    counting_mode = false;
    delay(500);
  }
 
  // If button 0 has been pressed (the start button),
  // we initialize the original program, that prints
  // the sensor data on the SD card, increases the counter
  // variable and changes the color of the display to blue
 
  if (counting_mode == true) {
 
    // print each of the sensor values
  Serial.print(temperature);
  Serial.print(",");
 
  Serial.print(humidity);
  Serial.print(",");
  Serial.print(pressure);
  Serial.print(",");
  Serial.print(light);
  Serial.print(",");
 
  Serial.print(Ax);
  Serial.print(",");
  Serial.print(Ay);
  Serial.print(",");
  Serial.print(Az);
  Serial.print(",");
 
  Serial.print(Gx);
  Serial.print(",");
  Serial.print(Gy);
  Serial.print(",");
  Serial.print(Gz);
  Serial.println(",");
  
  counter += 1;
 
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(4);
 
  carrier.display.setCursor(100, 70);
  carrier.display.print(counter);
  carrier.display.setCursor(20, 110);
  carrier.display.setTextSize(2);
  carrier.display.print("Measures taken");
 
  // wait 1 second to print again
  delay(1000);
  }
 
  // If button 4 has been pressed (the stop button),
  // we change the color of the display to red,
  // stop the counter, and print the message "Not recording" on the display
 
  else if (counting_mode == false) {
    carrier.display.fillScreen(ST77XX_RED); //red background
    carrier.display.setTextColor(ST77XX_WHITE); //white text
    carrier.display.setTextSize(4); //medium sized text
 
    carrier.display.setCursor(100, 70);
    carrier.display.print(counter);
    carrier.display.setCursor(20, 110);
    carrier.display.setTextSize(2);
    carrier.display.print("Not recording");
 
    carrier.display.setCursor(20, 200); //sets new position for printing (x and y)
    carrier.display.print("START");
    carrier.display.setCursor(160, 200); //sets new position for printing (x and y)
    carrier.display.println("STOP");
 
    delay(1000);
  }
 
}