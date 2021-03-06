// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>


const char THING_ID[] = "";

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

void onCloudBeansChange();
void onCloudGuessConfirmChange();
void onCloudBeansConfirmChange();
void onCloudGuessChange();

int cloudBeans;
bool cloudGuess_confirm;
bool boardBeans_Ready;
String results;
bool cloudBeans_confirm;
int boardGuess;
int cloudGuess;
bool boardGuess_Ready;
int boardBeans;

void initProperties(){

  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(cloudBeans, READWRITE, ON_CHANGE, onCloudBeansChange);
  ArduinoCloud.addProperty(cloudGuess_confirm, READWRITE, ON_CHANGE, onCloudGuessConfirmChange);
  ArduinoCloud.addProperty(boardBeans_Ready, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(results, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(cloudBeans_confirm, READWRITE, ON_CHANGE, onCloudBeansConfirmChange);
  ArduinoCloud.addProperty(boardGuess, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(cloudGuess, READWRITE, ON_CHANGE, onCloudGuessChange);
  ArduinoCloud.addProperty(boardGuess_Ready, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(boardBeans, READ, ON_CHANGE, NULL);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
