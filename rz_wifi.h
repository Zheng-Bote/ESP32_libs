/*
LIB: 
  rz_wifi.h
DESC: 
  Arduino library for ESP32 for etablsihing WiFi network

SOURCE: 
  https://github.com/Zheng-Bote/ESP32_libs

Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.1.0   | 2019-10-27 | RZheng           | created
0.3.0   | 2022-02-26 | RZheng           | modified 
1.0.0   | 2022-02-27 | RZheng           | finalized 

*/

#ifndef rz_wifi_h
#define rz_wifi_h

#include "Arduino.h"

class RZ_WiFi {
  public:
    RZ_WiFi(char *ssid, char *password);
    bool startWiFi();
    IPAddress getIpAddr();
    bool startMDNS(std::string hostId);

  private:
    char *_ssid;
    char *_pwd;
    int _counter;
    IPAddress _ipAddr;
    std::string _mdnsHost;
    
  ~RZ_WiFi() {
  }
};

#endif 
