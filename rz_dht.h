/*
TITLE: 
	rz_dht.h

BRIEF:
	library

DESC: 
	Arduino lib for ESP32 DHT11, DHT22 (AM2302), DHT21 (AM2301) Sensors

SOURCE: 
	https://github.com/Zheng-Bote/esp32_libs

SYNTAX:
	#include "rz_dht.h"
	RZ_DHT *dhtsensor = new RZ_DHT();
	
	void readData();
	String getTemperature();
	String getHumidity();
    bool getSensorStatus();

RETURN:
	void // read current sensor data
	String temperature // 23.15 // °C
	String humidity // 45.55 // %
	bool error // true = sensor error, false = sensor reading ok

HISTORY:
Version | Date       | Developer  | Comments
------- | ---------- | ---------- | ---------------------------------------------------------------
1.0.0   | 2022-02-26 | RZheng     | created 
1.1.0   | 2022-02-27 | RZheng     | fixed: some low quality DHT sensors needs 1 second pause 

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
