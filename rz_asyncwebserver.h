/*
TITLE: 
	rz_asyncwebserver.h

BRIEF:
	header only library

DESC: 
	Arduino library for ESP32, async webserver
	* don't use, deprecated

SOURCE: 
	https://github.com/Zheng-Bote/esp32_libs

SYNTAX:
	#include "rz_asyncwebserver.h"

RETURN:
	void

HISTORY:
Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.0.1   | 2018-10-13 | RZheng           | created 

*/

#include "Arduino.h"

#ifndef rz_asyncwebserver
#define rz_asyncwebserver

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer webserver(80);


void notFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "Not found");
}

void rz_asyncwebserver_start()
{
    webserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });

    webserver.onNotFound(notFound);

    webserver.begin();
}

#endif 
