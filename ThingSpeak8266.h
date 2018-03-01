#ifndef ThingSpeak8266_h
#define ThingSpeak8266_h
#include <inttypes.h>
#include "Print.h"

#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
#endif

// Version 1.0.0

class ThingSpeak8266 {
  public:
    void ThingSpeak8266::init(char * key);
    void ThingSpeak8266::ConnectWifi(char *ssid, char *password);
    int ThingSpeak8266::Status();
    void ThingSpeak8266::Data(int ref, char *content);
    void ThingSpeak8266::Send();
    bool ThingSpeak8266::sendCmd(char *msg, char *expected);

    char fielddata[50];
    
  private:
    float data[8];
    bool hasdata[8];
    char apikey[17];
    int status;

};

#endif

