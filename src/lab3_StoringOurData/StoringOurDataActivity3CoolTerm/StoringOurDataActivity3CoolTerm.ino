#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
// variables
float temperature = 0;
float humidity = 0;
float pressure = 0;
int light = 0;
int none;
 
// gyroscope
float Gx, Gy, Gz;
 
//accelerometer
float Ax, Ay, Az;
 
//track how many measurements have been made
int counter = 0;
 
void setup() {
  Serial.begin(115200);
 
  delay(1500);  //Wait to open the Serial monitor to start the program and see details on errors
 
  //Initialize the MKRIoT carrier and output any errors in the serial monitor
  CARRIER_CASE = true;
  carrier.begin();
 
  // init the CSV file with headers
  Serial.println("temperature,humidity,pressure,light,Ax,Ay,Az,Gx,Gy,Gz");
}
 
void loop() {
  // read the sensors values
  temperature = carrier.Env.readTemperature(FAHRENHEIT);
  humidity = carrier.Env.readHumidity();
  pressure = carrier.Pressure.readPressure();
 
  if (carrier.Light.colorAvailable()) {
    carrier.Light.readColor(none, none, none, light);;
  }
 
  // read the IMU values
  carrier.IMUmodule.readAcceleration(Ax, Ay, Az);
  carrier.IMUmodule.readGyroscope(Gx, Gy, Gz);
 
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