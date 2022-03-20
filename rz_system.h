/*
TITLE: 
	rz_system.h

BRIEF:
	library

DESC: 
  Arduino library for ESP32 systems

SOURCE: 
  https://github.com/Zheng-Bote/ESP32_libs

SYNTAX:
    #include "ESP32/rz_system.h"
    RZ_System *esp32System = new RZ_System();

RETURN:
    void doRestart();
    void doReset();
    uint8_t getChipRevision();
    uint8_t getCpuFreqMHz();
    uint32_t getFlashChipSize();
    std::string getHostId();
    std::string getHostName();
    uint64_t getChipId();
    uint16_t getChip();
    void doStartDeepSleep(unsigned long long TIME_TO_SLEEP);
    void ntpLocalTime(char *ntpServer, long gmtOffset_sec, int daylightOffset_sec);
    std::string getDateTimeString();

HISTORY:
Version | Date       | Developer  | Comments
------- | ---------- | ---------- | ------------------------------------------------------------------------
1.0.0   | 2022-02-26 | RZheng     | created
1.1.0   | 2022-02-27 | RZheng     | changed: deep sleep TIME_TO_SLEEP changed from int to unsigned long long 
1.1.1   | 2022-02-27 | RZheng     | fixed: hostname / MAC-Address

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
    std::string getHostName();
    uint64_t getChipId();
    uint16_t getChip();
    void doStartDeepSleep(unsigned long long TIME_TO_SLEEP);
    void ntpLocalTime(char *ntpServer, long gmtOffset_sec, int daylightOffset_sec);
    std::string getDateTimeString();
    
  private:
    char _hostId[23];
    std::string nodeId;
    uint64_t chipId;
    uint16_t chip;
    char _baseMacChr[18];

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
