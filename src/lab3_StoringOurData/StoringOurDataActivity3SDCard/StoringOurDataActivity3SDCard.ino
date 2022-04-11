/*
  EIoTK_Activity_03
 
  Read information from the all of the sensors
  on the IoT carrier and store it on a
  CSV file inside an SD card. Connect the SD
  card to the slot on the IoT carrier. The amount
  of measurements taken will also be printed on 
  the IoT carrier's display.
 
  This example uses the IoT carrier and the MKR WiFi 1010.
    
  Based on code by:
  (c) 2019 D. Cuartielles for Arduino
 
  Written by:
  (c) 2020 K. SÃ¶derby for Arduino
  
  Reworked by:
  (c) 2021 L. Aljundi for Arduino
  
  This code is Free Software licensed under GPLv3
*/
 
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
// variables
float temperature = 0;
float humidity = 0;
float pressure = 0;
int light = 0;
int r,g,b;
 
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
 
  //Initialize the MKR IoT carrier and output any errors in the serial monitor
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
  delay(1000);
 
  // read the sensors values
  temperature = carrier.Env.readTemperature(FAHRENHEIT);
  humidity = carrier.Env.readHumidity();
  pressure = carrier.Pressure.readPressure();
  
  while(!carrier.Light.colorAvailable()){
    delay(5);
  }
  carrier.Light.readColor(r, g, b, light);
  
  // read the IMU values
  carrier.IMUmodule.readAcceleration(Ax, Ay, Az);
  carrier.IMUmodule.readGyroscope(Gx, Gy, Gz);
  
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
 
  carrier.display.fillScreen(ST77XX_BLACK); //red background
  carrier.display.setTextColor(ST77XX_WHITE); //white text
  carrier.display.setTextSize(4); //medium sized text
 
  carrier.display.setCursor(100, 70);
  carrier.display.print(counter);
  carrier.display.setCursor(35, 125);
  carrier.display.setTextSize(2);
  carrier.display.print("Measures taken");
  
  // wait 1 second to print again
  delay(1000);
}
