/*
LIB: 
  rz_system.h
DESC: 
  Arduino library for ESP32 systems

SOURCE: 
  https://github.com/Zheng-Bote/ESP32_libs

Version | Date       | Developer  | Comments
------- | ---------- | ---------- | ---------------------------------------------------------------
1.0.0   | 2022-02-26 | RZheng     | created 

*/

#ifndef rz_system_h
#define rz_system_h

#include "Arduino.h"

class RZ_System {
  public:
    RZ_System();
    void doRestart();
    void doReset();
    uint8_t getChipRevision();
    uint8_t getCpuFreqMHz();
    uint32_t getFlashChipSize();
    std::string getHostId();
    uint64_t getChipId();
    uint16_t getChip();
    void doStartDeepSleep(int TIME_TO_SLEEP);
    void ntpLocalTime(char *ntpServer, long gmtOffset_sec, int daylightOffset_sec);
    std::string getDateTimeString();
    
  private:
    char _hostId[23];
    std::string nodeId;
    uint64_t chipId;
    uint16_t chip;

    char year[5];
    char month[3];
    char day[3];
    char hour[3];
    char minutes[3];
    char seconds[3];
    
  ~RZ_System() {
  }
};

#endif
