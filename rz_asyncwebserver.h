/* RRBBP
 * 2018-10-13
 * v0.01
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
