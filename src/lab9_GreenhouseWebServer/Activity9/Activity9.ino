#include <WiFiNINA.h>
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
char ssid[] = "";                    //  your network SSID (name) between the " "
char pass[] = "";                   // your network password between the " "
int keyIndex = 0;                  // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;      // connection status
WiFiServer server(80);           // server socket
 
WiFiClient client = server.available();
 
int moistPin = A5;  //Set the analog pin
 
String relayState = "";
 
int moistValue;
float temperature;
float humidity;
int light;
 
void setup() {
  Serial.begin(9600);
  delay(1500);
  CARRIER_CASE = true;
  carrier.begin();
  carrier.display.setTextSize(2);
  carrier.display.setCursor(20, 50); 
  
  enable_WiFi();
  connect_WiFi();
  server.begin();
  printWifiStatus();
}
 
void loop() {
  client = server.available();
 
  if (client) {
    readSensors();
    printWEB();
  }
}
 
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
 
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
 
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
 
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.println("  ** Successfully        Connected **");
  carrier.display.println("  Find link in the    Serial Monitor");
}
 
void enable_WiFi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
 
  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
}
 
void connect_WiFi() {
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    carrier.display.println("Waiting for        Connection ...");
    // wait 10 seconds for connection:
    delay(10000);
  }
}
 
 
void readSensors() {
 
  int rawMoistValue = analogRead(moistPin);
  moistValue = map(rawMoistValue, 0, 1023, 100, 0);
 
  temperature = carrier.Env.readTemperature(FAHRENHEIT);
  humidity = carrier.Env.readHumidity();
 
  if (carrier.Light.colorAvailable()) {
    // read the color
    int none; //not gonna be used
    carrier.Light.readColor(none, none, none, light);
    
  }
}
 
void printWEB() {
 
  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
 
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
 
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // the content of the HTTP response follows the header:
            client.println("<!DOCTYPE HTML>");
            client.println("<meta http-equiv=\"refresh\" content=\"5\">");
            client.print("<head>");
            client.print("<script src='https://kit.fontawesome.com/0a4ce480d6.js'></script>");
            client.print("<style>");
            client.print(".textField {font-size: 48px; font-family: Verdana, Geneva, Tahoma, sans-serif;  margin-top: 150px;}");
 
            //moisture
            if (moistValue > 40) {
              client.print(".fa-tree {font-size: 48px; color: green;}");
            }
            else {
              client.print(".fa-tree {font-size: 48px; color: red;}");
            }
 
            //humidity
            if (humidity >= 30 && humidity <= 50) {
              client.print(".fa-tint {font-size: 48px; color: green;}");
            }
            else {
              client.print(".fa-tint {font-size: 48px; color: red;}");
            }
 
            //light
            if (light > 300) {
              client.print(".fa-sun {font-size: 48px; color: green;}");
            }
            else {
              client.print(".fa-sun {font-size: 48px; color: red;}");
            }
            
            //Temperature
            if (temperature >= 22 && temperature <= 28) {
              client.print(".fa-thermometer-quarter {font-size: 48px; color: green;}");
            }
            else {
              client.print(".fa-thermometer-quarter {font-size: 48px; color: red;}");
            }
 
            if (relayState == "ON") {
              client.print(".fa-bolt {font-size: 48px; color: green;}");
            }
            else {
              client.print(".fa-bolt {font-size: 48px; color: red;}");
            }
 
 
            client.print(".on {border: none; background-color: green; color: white;font-size: 36px; padding: 15px; border-radius: 10px;}");
            client.print(".off {border: none; background-color: red; color: white; font-size: 36px; padding: 15px; border-radius: 10px;}");
 
            client.print("</style>");
            client.print("</head>");
 
            client.print("<body>");
            //create a div to contain our properties
            client.println("<center><div class='textField'>");
 
            //print moist level in plant
            client.println("<i class='fas fa-tree'></i>");
            client.print("The moisture level in your plant: ");
            client.print(moistValue);
            client.print(" %");
            client.println("<br><br>");
 
            //print light level
            client.println("<i class='fas fa-sun'></i>");
            client.print("Illuminance is: ");
            client.print(light);
            client.print(" LUX");
            client.println("<br><br>");
 
            //print humidity
            client.println("<i class='fas fa-tint'></i>");
            client.print("The local humidity is: ");
            client.print(humidity);
            client.print(" %");
            client.println("<br><br>");
 
            //print temperature
            client.println("<i class='fas fa-thermometer-quarter'></i>");
            client.print("The local temperature is: ");
            client.print(temperature);
            client.print(" celsius");
            client.println("<br><br>");
 
            //state of relay 
            client.println("<i class='fas fa-bolt'></i>");
            client.print("The relay is currently: ");
            client.print(relayState);
            client.println("<br><br>");
 
            //create the buttons
            client.print("<button class='on' type='submit' value='ON' onmousedown=location.href=");
            client.print("'/H\'");
            client.println(">RELAY ON</button>");
 
            client.print("<button class='off' type='submit' value='OFF' onmousedown=location.href=");
            client.print("'/L\'");
            client.println(">RELAY OFF</button>");
 
            //close the div
            client.println("</div>");
            client.println("</body>");
            client.println("</html>");
 
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
 
        if (currentLine.endsWith("GET /H")) {
          carrier.Relay1.open();
          relayState = "ON";
        }
        if (currentLine.endsWith("GET /L")) {
          carrier.Relay1.close();
          relayState = "OFF";
        }
 
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}