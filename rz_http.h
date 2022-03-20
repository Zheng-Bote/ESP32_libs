/*
TITLE: 
    rz_http.h

BRIEF:
    library

DESC: 
    Arduino lib for ESP32 http client. Gets the current firmware version on Github

SOURCE: 
    https://github.com/Zheng-Bote/ESP32_libs

SYNTAX:
    #include "rz_http.h"
    #include "rz_version.h"
    
    RZ_HTTP *httpclient = new RZ_HTTP();
    RZ_Version *versions = new RZ_Version();
    
    checkVersion(versions->checkVersions(appVersion, httpclient->checkFirmware()));  

RETURN:
    std::string checkFirmware();
    std::string getUpdVersion();

HISTORY:
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
