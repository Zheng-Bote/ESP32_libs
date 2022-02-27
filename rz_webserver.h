/*
LIB: 
  rz_webserver.h
DESC: 
  Arduino library for ESP32, just provides the html content

SOURCE: 
  https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client

Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.1.0   | 2022-02-26 | RZheng           | created 
1.0.0   | 2022-02-27 | RZheng           | lib created 

*/

#ifndef rz_webserver_h
#define rz_webserver_h

#include "Arduino.h"
#include <WebServer.h>

WebServer webServer(webserverPort);


void handleRoot() {
  digitalWrite(led, 1);
  const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">
  <head>
  <meta charset="utf-8">
  <title>DHT22 Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta http-equiv="refresh" content="15"/>
  <meta name="author" content="ZHENG Robert">
  <meta name="description" content="ESP32 DHT22 Wifi Webserver & MQTT client">
  
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {  font-size: 1.2rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #4B1D3F; color: white; font-size: 1.7rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); border-radius: 5px; }
    .cards { max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .card.temperature { color: #0e7c7b; }
    .card.humidity { color: #17bebb; }
    .card.pressure { color: #3fca6b; }
    .card.gas { color: #d62246; }
    .version {margin-top: 2px; font-size: 0.8rem; text-align: center;}
  </style>

  <script>
    async function getJsonData() {
      await fetch('/getjsonvals')
      .then(data => data.json())
      .then((json) => {
        document.getElementById("temp").innerHTML = json.temperature;
        document.getElementById("hum").innerHTML = json.humidity;
      })
      .catch((error) => {console.error(error);});
    }
  </script>
</head>
<body onload="getJsonData()">
  <div class="topnav">
    <h3>ESP32 DHT22 Wifi Webserver & MQTT client</h3>
  </div>
  <div class="version" id="version"></div>
  <div class="content">
    <div class="cards">
      <div class="card temperature">
        <h4><i class="fas fa-thermometer-half"></i> TEMPERATURE</h4><p><span class="reading"><span id="temp"><i class="fa fa-spinner fa-spin"></i></span> &deg;C</span></p>
      </div>
      <div class="card humidity">
        <h4><i class="fas fa-tint"></i> HUMIDITY</h4><p><span class="reading"><span id="hum"><i class="fa fa-cog fa-spin fa-fw"></i></span> &percnt;</span></p>
      </div>
    </div>
  </div>
  <script>
    checkVersion();
    async function checkVersion() {
      await fetch('/checkversion')
      .then(data => data.json())
      .then((json) => {
        if(json.isupdate === "true") {
          document.getElementById("version").innerHTML = '<mark style="font-size: 1rem;">a new Firmware v' + json.version + ' is available on <a href="https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client" alt="Github link" title="https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client">Github</a></mark>';
        }
        else {
          document.getElementById("version").innerHTML = "v" + json.version;
        }
      })
      .catch((error) => {console.error(error);});
    }
  </script>
</body>
</html>
)rawliteral";

  webServer.send(200, "text/html", index_html);
  digitalWrite(led, 0);
}


#endif 
