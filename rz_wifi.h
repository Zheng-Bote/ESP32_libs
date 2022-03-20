/*
TITLE: 
  rz_wifi.h

BRIEF:
	library

DESC: 
  Arduino library for ESP32 for etablsihing WiFi network

SOURCE: 
  https://github.com/Zheng-Bote/ESP32_libs

SYNTAX:
	#include "ESP32/rz_wifi.h"
	RZ_WiFi *wifi = new RZ_WiFi(char *ssid, char *password);
	
	bool wifi->startWiFi();
    IPAddress wifi->getIpAddr();
    bool wifi->startMDNS(std::string hostId);

RETURN:
	void

HISTORY:
Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.1.0   | 2019-10-27 | RZheng           | created
0.3.0   | 2022-02-26 | RZheng           | modified 
1.0.0   | 2022-02-27 | RZheng           | finalized 
1.1.0   | 2022-03-19 | RZheng           | Constructor for manual WiFi or WiFiManager 

*/

#ifndef rz_wifi_h
#define rz_wifi_h

#include "Arduino.h"

class RZ_WiFi {
  public:
    // for WiFiMananger
    RZ_WiFi();
    // for manual WiFi
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


/*
    WL_CONNECTION_LOST: assigned when the connection is lost;
    WL_DISCONNECTED: assigned when disconnected from a network;
    https://www.arduino.cc/en/Reference/WiFiClientAvailable
*/
