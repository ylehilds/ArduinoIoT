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
 
// file object
File dataFile;
 
void setup() {
  Serial.begin(9600);
 
  //Initialize the IoTSK carrier and output any errors in the serial monitor
  CARRIER_CASE = true;
  carrier.begin();
 
  // init SD card
  if (!SD.begin(SD_CS)) {
    carrier.display.setTextSize(2);
    carrier.display.setCursor(35, 70);
    carrier.display.print("SD card failed");
    carrier.display.setCursor(45, 110);
    carrier.display.print("to initialise");
    while (1);
  }
 
  // init the logfile
  dataFile = SD.open("log-0000.csv", FILE_WRITE);
  delay(1000);
 
  // init the CSV file with headers
  dataFile.println("temperature,humidity,pressure,light,Ax,Ay,Az,Gx,Gy,Gz");
 
  // close the file
  dataFile.close();
  delay(100);
}
 
void loop() {
  // init the logfile
  dataFile = SD.open("log-0000.csv", FILE_WRITE);
 
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
    dataFile.print(temperature);
    dataFile.print(",");
 
    dataFile.print(humidity);
    dataFile.print(",");
    dataFile.print(pressure);
    dataFile.print(",");
    dataFile.print(light);
    dataFile.print(",");
 
    dataFile.print(Ax);
    dataFile.print(",");
    dataFile.print(Ay);
    dataFile.print(",");
    dataFile.print(Az);
    dataFile.print(",");
 
    dataFile.print(Gx);
    dataFile.print(",");
    dataFile.print(Gy);
    dataFile.print(",");
    dataFile.print(Gz);
    dataFile.println(",");
    dataFile.close();
 
    counter += 1;
 
    carrier.display.fillScreen(ST77XX_BLUE); //red background
    carrier.display.setTextColor(ST77XX_WHITE); //white text
    carrier.display.setTextSize(4); //medium sized text
 
    carrier.display.setCursor(100, 70);
    carrier.display.print(counter);
    carrier.display.setCursor(20, 110);
    carrier.display.setTextSize(2);
    carrier.display.print("Measures taken");
 
    carrier.display.setCursor(20, 200); //sets new position for printing (x and y)
    carrier.display.print("START");
    carrier.display.setCursor(160, 200); //sets new position for printing (x and y)
    carrier.display.println("STOP");
 
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