 /*
TITLE: 
    rz_bme680.h

BRIEF:
    Arduino lib for ESP32 BME680 sensor

DESC: 
    Arduino ESP32 library for BME680 sensor (temperature, humidity, pressure, gas)

SOURCE: 
    https://github.com/Zheng-Bote/ESP32_libs

SYNTAX:
    #include "rz_bme680.h" | #include "ESP32/rz_bme680.h"
    
    RZ_BME680 *bme680sensor = new RZ_BME680();
    bme680sensor->readData();
    if(bme680sensor->getSensorStatus()) {
        Serial.println("\n-- BME680 sensor failed.\n");
    }
    else {
        Serial.print("-- Temperature: "); Serial.println(bme680sensor->getTemperature());
        Serial.print("-- Humidity: "); Serial.println(bme680sensor->getHumidity());
        Serial.print("-- Pressure: "); Serial.println(bme680sensor->getPressure());
        Serial.print("-- Gas: "); Serial.println(bme680sensor->getGas());
    }

RETURN:
    void readData();
    String getTemperature();
    String getHumidity();
    String getPressure();
    String getGas();
    bool getSensorStatus();

HISTORY:
Version | Date       | Developer  | Comments
------- | ---------- | ---------- | ---------------------------------------------------------------
1.0.0   | 2022-02-27 | RZheng     | created 

*/

#ifndef rz_bme680_h
#define rz_bme680_h

#include "Arduino.h"

class RZ_BME680 {
  public:
    RZ_BME680();
    void readData();
    String getTemperature();
    String getHumidity();
    String getPressure();
    String getGas();
    bool getSensorStatus();

  private:
    String _bme680_temperature;
    String _bme680_humidity;
    String _bme680_pressure;
    String _bme680_gasResistance;
    bool _sensorError;
    
  ~RZ_BME680() {
  }
};

#endif
