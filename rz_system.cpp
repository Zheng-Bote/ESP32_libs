// 1.1.0

#include "Arduino.h"
#include "rz_system.h"

#include <WiFi.h>
#include "time.h"

RZ_System::RZ_System() {
  chipId = ESP.getEfuseMac(); // The chip ID is essentially its MAC address(length: 6 bytes).
  chip = (uint16_t)(chipId >> 32);
}

std::string RZ_System::getHostId() {
  snprintf(_hostId, 23, "ESP32-%08X", (uint32_t)chipId);
  nodeId = _hostId;
  return nodeId;
}

std::string RZ_System::getHostName(){
  uint64_t chipid;  

  chipid=ESP.getEfuseMac(); 
  sprintf(_baseMacChr, "ESP32-%04X",(uint16_t)(chipid>>32));
  
  return _baseMacChr;
}

uint64_t RZ_System::getChipId() {
  return chipId;
}

uint16_t RZ_System::getChip() {
  return chip;
}

void RZ_System::doRestart() {
  ESP.restart();
}
void RZ_System::doReset() {
  //ESP.reset();
}

uint8_t RZ_System::getChipRevision() {
  return getChipRevision();
}

uint8_t RZ_System::getCpuFreqMHz() {
  return getCpuFreqMHz();
}

uint32_t RZ_System::getFlashChipSize() {
  return getFlashChipSize();
}

void RZ_System::doStartDeepSleep(unsigned long long TIME_TO_SLEEP) {
  // Conversion factor for micro seconds to seconds 
  const int uS_TO_S_FACTOR = 1000000; 
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void RZ_System::ntpLocalTime(char *ntpServer, long gmtOffset_sec, int daylightOffset_sec) {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("-- Failed to obtain NTP time");
    return;
  }

  // day
  strftime(day,3, "%d", &timeinfo);
  // month
  strftime(month,3, "%m", &timeinfo);
  // year
  strftime(year,5, "%Y", &timeinfo);
  // hour
  strftime(hour,3, "%H", &timeinfo);
  // minutes
  strftime(minutes,3, "%M", &timeinfo);
  // seconds
  strftime(seconds,3, "%S", &timeinfo);
}

std::string RZ_System::getDateTimeString() {
  std::string dt;
  dt = year;
  dt += "-";
  dt += month;
  dt += "-";
  dt += day;
  dt += " ";
  dt += hour;
  dt += ":";
  dt += minutes;
  dt += ":";
  dt += seconds;
  return dt;
}
