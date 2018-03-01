#include "ThingSpeak8266.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

#ifndef HAVE_HWSERIAL1
SoftwareSerial Serial1(6, 7); // RX, TX
#endif


void ThingSpeak8266::init(char * key)
{
  strcpy(fielddata, "");
  strcpy(apikey, key);
  status = 0;
  Serial1.begin(9600);
}

void ThingSpeak8266::ConnectWifi(char *ssid, char *password) {
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  ThingSpeak8266::sendCmd("AT+CWMODE=1", "OK");
  delay(1500);

  if (ThingSpeak8266::sendCmd("AT+CWJAP?", ssid)) {
    Serial.println("Already connected to wifi");
  } else {
    char myCommand[200];
    sprintf(myCommand, "AT+CWJAP=\"%s\",\"%s\"", ssid, password);
    if (ThingSpeak8266::sendCmd(myCommand, "WIFI GOT IP")) {
      Serial.println("Connected to Wifi");
    } else {
      Serial.println("Failed to connect to Wifi");
    }
  }
  delay(1500);
  if (ThingSpeak8266::sendCmd("AT+CIFSR", "CIFSR:STAIP")) {
    Serial.println("IP addressed achieved");
  } else {
    Serial.println("No IP address");
  }  

  //Allow multiple connections
  ThingSpeak8266::sendCmd("AT+CIPMUX=1", "OK");

  delay(5000);
}

void ThingSpeak8266::Data(int ref, char *content) {
  sprintf(fielddata, "%s&field%i=%s", fielddata, ref, content);
}

int ThingSpeak8266::Status() {
  return status;
}

void ThingSpeak8266::Send() {
  char myCommand[200];
  sprintf(myCommand, "GET http://api.thingspeak.com/update?api_key=%s%s", apikey, fielddata);

  int len = strlen(myCommand) + 2;
  char prepstr[20];
  sprintf(prepstr, "AT+CIPSEND=4,%i", len);

  ThingSpeak8266::sendCmd("AT+CIPSTART=4,\"TCP\",\"52.5.13.84\",80", "CONNECT");
  ThingSpeak8266::sendCmd(prepstr, "");
  ThingSpeak8266::sendCmd(myCommand, "42");
  strcpy(fielddata, "");
}



bool ThingSpeak8266::sendCmd(char *msg, char *expected) {
  char outp[80] = "";
  char rsp[80];
  bool foundit = (strlen(expected) == 0);
  int c;
  char ch;

  while (Serial1.available()) {
    ch = Serial1.read();
//    Serial.print(ch);
  }
//  Serial.println("");
  Serial.print("Sending:");
  Serial.println(msg);
  Serial1.println(msg);
  delay(1000);
  Serial.setTimeout(10000);

  while (Serial1.available() && !foundit) {
//     Serial.println("Input available");
    c = Serial1.readBytesUntil('\r', rsp, 80);

//    Serial.print("Chars received: ");
//    Serial.println(c);

    int j = 0;
    for (int i = 0; i < c; i++) {
      if ((rsp[i] != '\r') && (rsp[i] != '\n')) {
        outp[j] = rsp[i];
        j++;
      }
    }
    outp[j] = '\0';

//    Serial.print("\"");
//    Serial.print(outp);
//    Serial.print("\"  ");
    if (strstr(outp, expected)) {
      foundit = true;
//      Serial.print("matched ");
    }
//    Serial.println("");
    delay(1000);  
  }
  return foundit;
}

