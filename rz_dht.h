/*
LIB: 
  rz_dht.h
DESC: 
  Arduino lib for ESP32 DHT11, DHT22 (AM2302), DHT21 (AM2301) Sensors

SOURCE: 
  https://github.com/Zheng-Bote/ESP32_libs

Version | Date       | Developer  | Comments
------- | ---------- | ---------- | ---------------------------------------------------------------
1.0.0   | 2022-02-26 | RZheng     | created 

*/

#ifndef rz_dht_h
#define rz_dht_h

#include "Arduino.h"
class RZ_DHT {
  public:
    RZ_DHT();
    void readData();
    String getTemperature();
    String getHumidity();
    bool getSensorStatus();

  private:
    float _dhtTemperature;
    float _dhtHumidity;
    bool _sensorError;
    
  ~RZ_DHT() {
  }
};

#endif
