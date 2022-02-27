/*
LIB: 
  rz_http.h
DESC: 
  Arduino lib for ESP32 http client. Checking for firmware updates on Github

SOURCE: 
  https://github.com/Zheng-Bote/ESP32_libs

Version | Date       | Developer  | Comments
------- | ---------- | ---------- | ---------------------------------------------------------------
1.0.0   | 2022-02-26 | RZheng     | created 

*/

#ifndef rz_http_h
#define rz_http_h

#include "Arduino.h"



class RZ_HTTP {
  public:
    RZ_HTTP();
    std::string checkFirmware();
    std::string getUpdVersion();

  private:
    String _payload;
    
  ~RZ_HTTP() {
  }
};

#endif 
