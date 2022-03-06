// 1.0.0

#include "Arduino.h"
#include "Zanshin_BME680.h"
#include "rz_bme680.h"


BME680_Class BME680; 
float altitude(const int32_t press, const float seaLevel = 1013.25);
float altitude(const int32_t press, const float seaLevel) {
  static float Altitude;
  Altitude = 44330.0 * (1.0 - pow(((float)press / 100.0) / seaLevel, 0.1903));  // Convert into meters
  return (Altitude);
}  


RZ_BME680::RZ_BME680() {
  _bme680_temperature = 0.0;
  _bme680_humidity = 0.0;
  _bme680_pressure = 0.0;
  _bme680_gasResistance = 0.0;
  _sensorError = false;
}

void RZ_BME680::readData() {
  int _counter = 0;
  static int32_t  temp, humidity, pressure, gas;  // BME readings
  static char     buf[16];                        // sprintf text buffer
  static float    alt;                            // Temporary variable
  
  while (!BME680.begin(I2C_STANDARD_MODE)) {  // Start BME680 using I2C, use first device found
    Serial.print(F("-- Unable to find BME680. Trying again in 5 seconds.\n"));
    delay(5000);
    if(_counter >= 10) {
      _sensorError = true;
      return;
    }
    _counter = _counter + 1;
  }  // of loop until device is located or counter limit reached
  
  //Serial.print(F("-- Setting 16x oversampling for all sensors\n"));
  BME680.setOversampling(TemperatureSensor, Oversample16);  // Use enumerated type values
  BME680.setOversampling(HumiditySensor, Oversample16);     // Use enumerated type values
  BME680.setOversampling(PressureSensor, Oversample16);     // Use enumerated type values
  //Serial.print(F("-- Setting IIR filter to a value of 4 samples\n"));
  BME680.setIIRFilter(IIR4);  // Use enumerated type values
  //Serial.print(F("-- Setting gas measurement to 320\xC2\xB0\x43 for 150ms\n"));  // "�C" symbols
  BME680.setGas(320, 150);  // 320�c for 150 milliseconds


  BME680.getSensorData(temp, humidity, pressure, gas);  // Get readings
  delay(1000);
  BME680.getSensorData(temp, humidity, pressure, gas);  // Get readings
  delay(1000);
  BME680.getSensorData(temp, humidity, pressure, gas);  // Get readings

  if (isnan(temp) || isnan(humidity) || isnan(pressure) || isnan(gas)) {    
    Serial.println("-- Failed to read from BME680 sensor!");
    _sensorError = true;
    return;
  }

  sprintf(buf, "%3d.%02d", (int8_t)(temp / 100), (uint8_t)(temp % 100));   // Temp in decidegrees
  _bme680_temperature = String(buf);
  
  sprintf(buf, "%3d.%03d", (int8_t)(humidity / 1000), (uint16_t)(humidity % 1000));  // Humidity milli-pct
  _bme680_humidity = String(buf);
  
  sprintf(buf, "%7d.%02d", (int16_t)(pressure / 100), (uint8_t)(pressure % 100));  // Pressure Pascals
  _bme680_pressure = String(buf);
  
  alt = altitude(pressure);                                                // temp altitude
  sprintf(buf, "%5d.%02d", (int16_t)(alt), ((uint8_t)(alt * 100) % 100));  // Altitude meters

  sprintf(buf, "%4d.%02d", (int16_t)(gas / 100), (uint8_t)(gas % 100));  // Resistance milliohms
  _bme680_gasResistance = String(buf);

  _bme680_temperature.trim();
  _bme680_humidity.trim();
  _bme680_pressure.trim();  
  _bme680_gasResistance.trim();
}

String RZ_BME680::getTemperature() {
  return String(_bme680_temperature);
}

String RZ_BME680::getHumidity() {
    return String(_bme680_humidity);
}

String RZ_BME680::getPressure() {
  return String(_bme680_pressure);
}

String RZ_BME680::getGas() {
    return String(_bme680_gasResistance);
}

bool RZ_BME680::getSensorStatus() {
  return _sensorError;
}
