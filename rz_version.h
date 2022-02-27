/*
LIB: 
  rz_version.h
DESC: 
  Arduino library, compares two semantic version strings
  - based on a function developed by Pankaj Choudhary. Unfortunately I've lost the contact and his website. Please contact me 

SOURCE: 
  https://github.com/Zheng-Bote/ESP32_libs

Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
        |            | Pankaj Choudhary | main function developed
1.0.0   | 2022-02-26 | RZheng           | lib created 


##### Usage:
// include lib
#include "rz_version.h"
//create instance
RZ_Version *versions = new RZ_Version();
// check versions: instance->checkVersions(std::string, std::string);
int returnValue = versions->checkVersions("1.0.0", "1.2.0"));
// returnValue:
0   // version1 == version2
1   // version1 > version2
2   // version1 < version2
255 // error

##### Example:
//# Source >>>

  #include "rz_version.h"
  
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
