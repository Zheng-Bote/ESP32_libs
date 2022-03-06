// 1.1.0

#include "Arduino.h"
#include "rz_dht.h"

#include <DHT.h>

// Digital pin connected to the DHT sensor
#define DHTPIN 27     
// DHT11, DHT22 (AM2302), DHT21 (AM2301)
#define DHTTYPE    DHT22

RZ_DHT::RZ_DHT() {
  _dhtTemperature = 0.0;
  _dhtHumidity = 0.0;
  _sensorError = false;
}

void RZ_DHT::readData() {
  // fix for some low quality sensors
  delay(1000);
  
  DHT *dht = new DHT(DHTPIN, DHTTYPE);
  dht->begin();
  
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  _dhtTemperature = dht->readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float _dhtTemperature = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(_dhtTemperature)) {    
    Serial.println("-- Failed to read from DHT sensor!");
    _sensorError = true;
  }

  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  _dhtHumidity = dht->readHumidity();

  if (isnan(_dhtHumidity)) {
    Serial.println("-- Failed to read from DHT sensor!");
    _sensorError = true;
  }
  delete dht;
}

String RZ_DHT::getTemperature() {
  return String(_dhtTemperature);
}

String RZ_DHT::getHumidity() {
    return String(_dhtHumidity);
}

bool RZ_DHT::getSensorStatus() {
  return _sensorError;
}
