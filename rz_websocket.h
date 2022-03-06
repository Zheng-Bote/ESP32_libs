/*
TITLE: 
	websocket.h

BRIEF:
	header only library

DESC: 
	Arduino library for ESP32, just provides the html content
	* don't use, deprecated

SOURCE: 
	https://github.com/Zheng-Bote/esp32_libs

SYNTAX:
	#include "rz_websocket.h"
	void rz_webserver_start()

RETURN:
	void

HISTORY:
Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.0.2   | 2018-10-14 | RZheng           | created 

*/

#include "Arduino.h"

#ifndef rz_websocket
#define rz_websocket


#include <WiFi.h>
#include <WebSocketServer.h>

  
WiFiServer webserver(80);
WebSocketServer webSocketServer;


void rz_webserver_start()
{
  webserver.begin();
}

 

#endif 


/********************** README *********************
 
 ### ESP32 Main =>
 
 #include "rz_websocket.h"
 
 void setup()
 {
    Serial.begin(115200);
    delay(10);
    // ... setup your WiFi and so on ...

    rz_webserver_start();
 }
 
void loop()
{
  WiFiClient client = webserver.available();
  if (client.connected() && webSocketServer.handshake(client)) 
  {
    String data;      
    while (client.connected()) 
    {
      data = webSocketServer.getData();
      if (data.length() > 0) 
      {
        Serial.println(data);
        webSocketServer.sendData(data);
      }
      delay(10); // Delay needed for receiving the data correctly
    }
    Serial.println("The client disconnected");
    delay(100);
  }
   
  delay(100);
}

### ESP32 Main <=

### Websocket Client =>

#!/usr/bin/python

import websocket
import time
 
ws = websocket.WebSocket()
ws.connect("ws://192.168.xxx.xxx:80/")
 
i = 0
nrOfMessages = 200
 
while i<nrOfMessages:
    ws.send("message nr: " + str(i))
    result = ws.recv()
    print(result)
    i=i+1
    time.sleep(1)
 
ws.close() 

### Websocket Client <= 

*/
