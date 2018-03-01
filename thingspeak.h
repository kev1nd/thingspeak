#ifndef thingspeak_h
#define thingspeak_h
#include <inttypes.h>
#include "Print.h"

#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
#endif


class ThingSpeak {
  public:
    void ThingSpeak::init(char * key);
    void ThingSpeak::ConnectWifi(char *ssid, char *password);
    int ThingSpeak::Status();
    void ThingSpeak::Data(int ref, char *content);
    void ThingSpeak::Send();
    bool ThingSpeak::sendCmd(char *msg, char *expected);

    char fielddata[50];
    
  private:
    float data[8];
    bool hasdata[8];
    char apikey[17];
    int status;

};

#endif

