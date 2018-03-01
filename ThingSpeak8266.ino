#include "ThingSpeak8266.h"

#include "settings.h"
// Defined in "settings.h" ...
//char ssid[15] = "XXXXXXXX"; // Wifi SSID
//char pass[15] = "XXXXXXXX"; // Wifi Password
//char apikey[] = "XXXXXXXX"; // Thingspeak write key

ThingSpeak thingspeak;
float mydata = 0.0;

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Starting...");
  thingspeak.init(apikey);
  thingspeak.ConnectWifi(ssid, pass);

}

void loop() {
  mydata = mydata + 0.3;
  char fielddata[12] = "";
  dtostrf(mydata, 4, 2, fielddata);
  thingspeak.Data(1, fielddata);
  thingspeak.Send();

  delay(30000);
}




