/*
  IoT Explore Kit - Activity 10
 
  Retrieves weather data from openweathermap.org and parses the data
  using the Arduino_JSON library. The different weather data can then
  be navigated through using capacative buttons on the IoT carrier. Each time
  button 1 is pressed, it updates the display with data from a new location
  that is inputted at the start of this code, e.g. San Francisco, US or London, UK
 
  More information on how to use the Open Weather Map API, refer to: https://openweathermap.org/api
 
  This example uses the IoT carrier and the MKR WiFi 1010.
 
  Based on code by (c) 2017 Officine Innesto
  Link: https://create.arduino.cc/projecthub/officine/getting-weather-data-655720
 
  (c) 2020 K. SÃ¶derby for Arduino
  (c) 2021 L. Aljundi for Arduino
 
  This code is Free Software licensed under GPLv3
*/
#include <WiFiNINA.h>
#include <Arduino_JSON.h>
 
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
char ssid[] = ""; //  your network NAME between ""
char pass[] = "";//  your network PASSWOR between ""
 
String apiKey = ""; //paste weather map API KEY between ""
 
//the cities you want the weather for
String location = "Orem, US";
String location2 = "Fortaleza, BR";
 
bool changeLocation = false;
 
int status = WL_IDLE_STATUS;
char server[] = "api.openweathermap.org";
 
WiFiClient client;
 
String cityName;
String weatherDescription;
 
double temperature;
double feelsLike;
double lon;
double lat;
double pressure;
double windSpeed;
 
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
 
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // wait 1 seconds for connection:
    delay(1000);
  }
  Serial.println("Connected to wifi");
  delay(1500);
  //Initialize the MKR IoT carrier
  CARRIER_CASE = true;
  carrier.begin();
 
  //Retrieve data from the API
  updateWeather();
}
 
void loop() {
 
  carrier.Buttons.update();
 
  if (carrier.Buttons.onTouchDown(TOUCH0)) {
    carrier.display.fillScreen(ST7735_BLACK);
    carrier.display.setCursor(20, 60);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    carrier.display.print("Updating data");
    delay(500);
    carrier.display.print(".");
    delay(500);
    carrier.display.print(".");
    delay(500);
    carrier.display.print(".");
    delay(500);
    carrier.display.print(".");
 
    updateWeather();
 
    carrier.display.fillScreen(ST7735_BLACK);
    carrier.display.setCursor(20, 60);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    carrier.display.println("Update Complete");
    carrier.display.setCursor(20, 110);
    carrier.display.println("Weather data from:");
    carrier.display.setCursor(20, 160);
    carrier.display.setTextSize(3);
 
    if (changeLocation == true) {
      carrier.display.println(location);
    }
    else if (changeLocation == false) {
      carrier.display.println(location2);
    }
    delay(1000);
  }
 
  if (carrier.Buttons.onTouchDown(TOUCH1)) {
    carrier.display.fillScreen(ST7735_BLACK);
    carrier.display.setCursor(20, 60);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(3);
    carrier.display.println(cityName);
    carrier.display.setCursor(20, 90);
    carrier.display.println("Temperature: ");
    carrier.display.setCursor(60, 130);
    carrier.display.println(temperature);
    carrier.display.setCursor(50, 160);
    carrier.display.println("Fahrenheit");
    delay(500);
  }
  if (carrier.Buttons.onTouchDown(TOUCH2)) {
    carrier.display.fillScreen(ST7735_BLACK);
    carrier.display.setCursor(20, 60);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(3);
    carrier.display.println(cityName);
    carrier.display.setCursor(20, 90);
    carrier.display.println(" Feels like: ");
    carrier.display.setCursor(60, 130);
    carrier.display.println(feelsLike);
    carrier.display.setCursor(50, 160);
    carrier.display.println("Fahrenheit");
    delay(500);
  }
  if (carrier.Buttons.onTouchDown(TOUCH3)) {
    carrier.display.fillScreen(ST7735_BLACK);
    carrier.display.setCursor(20, 60);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(3);
    carrier.display.println(cityName);
    carrier.display.setCursor(40, 90);
    carrier.display.print("Weather: ");
    carrier.display.setCursor(10, 130);
    carrier.display.println(weatherDescription);
    delay(500);
  }
  if (carrier.Button4.onTouchDown()) {
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setCursor(20, 60);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    carrier.display.print(cityName);
    carrier.display.setCursor(20, 110);
 
    //We remove the longitude and latitude to make space
    /*
      carrier.display.println("Longitude: ");
      carrier.display.println(lon);
      carrier.display.setCursor(20, 150);
      carrier.display.println("Latitude: ");
      carrier.display.println(lat);
    */
 
    //Instead, we print the pressure and wind speed
    carrier.display.println("Pressure: ");
    carrier.display.println(pressure);
 
    carrier.display.setCursor(20, 140);
    carrier.display.println("Wind Speed: ");
    carrier.display.println(windSpeed);
    delay(500);
  }
}
 
 
void updateWeather() {
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.print("GET /data/2.5/weather?");
 
    //used to switch between locations
    changeLocation = !changeLocation;
 
    if (changeLocation == true) {
      client.print("q=" + location);
    }
    else {
      client.print("q=" + location2);
    }
 
    client.print("&appid=" + apiKey);
    client.print("&cnt=3");
    client.println("&units=imperial");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("unable to connect");
  }
  delay(1000);
 
  String line = "";
  if (client.connected()) {
    line = client.readStringUntil('\n');
    Serial.println(line);
    JSONVar myObject = JSON.parse(line);
 
    cityName = JSON.stringify(myObject["name"]);
    weatherDescription = JSON.stringify(myObject["weather"][0]["description"]);
 
    temperature = myObject["main"]["temp"];
    feelsLike = myObject["main"]["feels_like"];
    lon = myObject["coord"]["lon"];
    lat = myObject["coord"]["lat"];
 
    //the windSpeed and pressure variables are new additions
    windSpeed = myObject["wind"]["speed"];
    pressure = myObject["main"]["pressure"];
 
    carrier.Buzzer.sound(300);
    delay(300);
    carrier.Buzzer.noSound();
    delay(300);
    carrier.Buzzer.sound(300);
    delay(300);
    carrier.Buzzer.noSound();
  }
}