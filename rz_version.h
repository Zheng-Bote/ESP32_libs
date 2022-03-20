/*
TITLE: 
    rz_version.h

BRIEF: 
    header only library

DESC: 
    Arduino library, compares two semantic version strings
    - based on a function developed by Pankaj Choudhary. Unfortunately I've lost the contact and his website. Please contact me 

SOURCE: 
    https://github.com/Zheng-Bote/ESP32_libs

SYNTAX:
    #include "rz_version.h"
    RZ_Version *versions = new RZ_Version();
    int ret = versions->checkVersions("1.0.0", "1.1.0");

RETURN:
    int
    0: version 1 is equal version 2 (ok)
    1: version 1 is greater than version 2 (older version)
    2: version 1 is smaller than version 2 (update available)

HISTORY:
Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.0.0   | xxxx-xx-xx | Pankaj Choudhary | main function developed
1.0.0   | 2022-02-26 | RZheng           | lib created 

*/

#ifndef rz_version_h
#define rz_version_h

#include "Arduino.h"

class RZ_Version {
  public:
    RZ_Version();
    int checkVersions(std::string v1, std::string v2);
    void setUpdateVersion(std::string v2);
    std::string getUpdateVersion();

  private:
    std::string _updateVersion;
    
  ~RZ_Version() {
  }
};

#endif


/*
##### Example:
//# Source >>>

  #include "ESP32/rz_version.h"
  
  // create instance
  RZ_Version *versions = new RZ_Version();
  
  // handle return value from checkVersions
  void checkVersion(int ret) {
    switch (ret) {
      case 0: {Serial.println("case 0: current version is up to date"); break;}
      case 1: {Serial.println("case 1: current version is greater than Github version. Pls check"); break;}
      case 2: {Serial.println("case 2: a new Firmware is available on Github"); break;}
      default:
        {Serial.println("case default"); break;}
    }
  }

  checkVersion(versions->checkVersions("1.0.0", "0.1.0"));
  delay(1000);
  checkVersion(versions->checkVersions("1.0.0", "1.0.0"));
  delay(1000);
  checkVersion(versions->checkVersions("1.0.0", "1.1.0"));

//# <<< Source

*/
