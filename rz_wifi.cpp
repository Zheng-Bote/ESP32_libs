// 1.0.0

#include "Arduino.h"
#include "rz_wifi.h"

#include <WiFi.h>
#include <ESPmDNS.h>

 RZ_WiFi::RZ_WiFi(char *ssid, char *password) {
  _ssid = ssid;
  _pwd = password;
  _counter = 0;
}

bool RZ_WiFi::startWiFi() {
  // Serial.print(F("- Initializing WiFi\n"));
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if(_counter >= 20) {
      return false;
    }
    _counter = _counter + 1;
  }  

  _ipAddr = WiFi.localIP();
  
  return true;
}

IPAddress RZ_WiFi::getIpAddr() {
  return _ipAddr;
}

bool RZ_WiFi::startMDNS(std::string hostId) {
  if (MDNS.begin(hostId.c_str())) {
    return true;
  }
  return false;
}
