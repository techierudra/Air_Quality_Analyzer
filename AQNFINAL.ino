#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

const char* ssid = "WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
WiFiClient client;
unsigned long tsChannelID = 2118781; // ThingSpeak Channel ID
const char * tsWriteAPIKey = "F2JEFP42K5J4Q9O1"; //ThingSpeak Write API Key
int airQuality = 0;
const int fieldOne = 1;

int mq135 = A0; // smoke sensor is connected with the analog pin A0 

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  setup_wifi();
}

void loop()
{
  airQuality = analogRead(mq135);
  Serial.println(airQuality);
  pushData();
  delay(15000); // send data every 15 seconds
}

void setup_wifi(){
  WiFi.begin(ssid, password);
  delay(10);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void pushData()
{
  ThingSpeak.writeField(tsChannelID, fieldOne, airQuality, tsWriteAPIKey);
  delay(100); // wait for the data to be written to ThingSpeak
}
