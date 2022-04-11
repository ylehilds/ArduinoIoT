#include "arduino_secrets.h"
/* 
  Sketch generated by the Arduino IoT Cloud Thing "Activity2"
  https://create.arduino.cc/cloud/things/77fb646c-df2b-4d09-97fe-f690ed996d22 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float humidity;
  float temperature;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
unsigned long timestamp; //create the "time" variable that we will use to record how long the program has run for
 
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
 
  Serial.println("time,temperature,humidity"); //add the "time" column
  showConnectedMessage();
}
 
void loop() {
  ArduinoCloud.update();
  // Your code here 
  temperature = carrier.Env.readTemperature(FAHRENHEIT);
  humidity = carrier.Env.readHumidity();
  
  timestamp = millis(); //check how long the program has run for in milliseconds
  
  double seconds = timestamp / 1000; //divide by 1000 to get measurements in seconds 
  
  Serial.print(seconds); //print seconds to serial monitor
  Serial.print(",");
  
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(humidity);
    
  delay(1000);
}

void showConnectedMessage() {
  ArduinoCloud.update();
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextSize(3);
  carrier.display.setCursor(20, 70);
  carrier.display.println("Connection");
  carrier.display.setCursor(5, 110);
  carrier.display.println("Successful!");
  delay(500);
}