#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WiFiSerial.h"

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin("asgard_2g", "enaLkraP");
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  WSerial.begin("WiFi Serial tester");
}

void loop()
{
  WSerial.loop();
  WSerial.printf("Now is %lu\n", millis());
  delay(1000);
}