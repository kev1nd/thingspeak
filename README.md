# Think Speak Library for Arduino / ESP8266

Sends AT commands from an Arduino to an ESP8266 in order to transmit data to Thing Speak.

## Setting up.
The Arduino sketch is just for testing. To make the test run, you should create a file called "settings.h" in the same directory as your sketch.

Contents of the file would be similar to this (except with your wifi ssid, password and Thing Speak key)

```
#ifndef settings_h
#define settings_h

char ssid[15] = "xxxxxxxxxxxxxx";   // Wifi SSID
char pass[15] = "xxxxxxxx";         // Wifi Password
char apikey[] = "XXXXXXXXXXXXXXXX"; // Thingspeak write key

#endif
```
