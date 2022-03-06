/*
TITLE: 
	rz_ota.h

BRIEF:
	header only library

DESC: 
	Arduino library for ESP32 OTA firmware update
	* don't use, deprecated

SOURCE: 
	https://github.com/Zheng-Bote/esp32_libs

SYNTAX:
	#include "rz_ota.h"

RETURN:
	void

HISTORY:
Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.0.2   | 2018-10-14 | RZheng           | created 

*/

#include "Arduino.h"

#ifndef rz_ota
#define rz_ota

#include <HTTPClient.h>
#include <Update.h>

const int FW_VERSION = 1;
char* fwUrlBase = "http://192.168.178.99/ESP_FW/";

String host = "192.168.178.99";  // Host => bucket-name.s3.region.amazonaws.com
int port = 80;                  // Non https. For HTTPS 443. As of today, HTTPS doesn't work.
String urlPath = "/ESP_FW/";
String fwbin = "C4D9_v1.bin";    // placeholder , will be filled during runtime

int contentLength = 0;
bool isValidContentType = false;

// #####

int rz_EspFwCheck()
{
  int newVersion = FW_VERSION;
  Serial.print( "Current ESP32 firmware version: " );
  Serial.println( FW_VERSION );
  Serial.print( "Checking for ESP32 firmware update..." );

  String fwURL = String( fwUrlBase );
  fwURL.concat( WiFi_hostname );
  String fwVersionURL = fwURL;
  fwVersionURL.concat( ".version" );
  
  HTTPClient httpClient;
  httpClient.begin( fwVersionURL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) 
  {
    Serial.println("OK");
    
    String newFWVersion = httpClient.getString();

    newVersion = newFWVersion.toInt();  
    if( newVersion > FW_VERSION ) 
    {
      Serial.println("new ESP32 firmware v" + String(newVersion) + " available");
      fwURL.concat( "_v");
      fwURL.concat( newVersion );
      String fwImageURL = fwURL;
      fwImageURL.concat( ".bin" );
      Serial.print( "firmware link: " );
      Serial.println(fwImageURL);
      httpClient.end();
      return 0;
    }
    else
    {
      Serial.println("current ESP32 firmware is up2date");
      httpClient.end();
      return -1;
    }
  }
  else
  {
    Serial.print("NOK");
    Serial.println( "Firmware version check failed, got HTTP response code: " );
    Serial.println( httpCode );
    Serial.println(fwVersionURL);
    httpClient.end();
    return -1;
  }
}

String getHeaderValue(String header, String headerName) 
{
  return header.substring(strlen(headerName.c_str()));
}

int rz_EspFwUpd() 
{
  int newVersion = FW_VERSION;
  String fwURL, fwVersionURL, fwImageURL;
  
  Serial.print( "Current ESP32 firmware version: " );
  Serial.println( FW_VERSION );
  Serial.print( "Checking for ESP32 firmware update..." );

  fwURL = String( fwUrlBase );
  fwURL.concat( WiFi_hostname );
  fwVersionURL = fwURL;
  fwVersionURL.concat( ".version" );
  fwImageURL = "";
  
  HTTPClient httpClient;
  httpClient.begin( fwVersionURL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) 
  {
    Serial.println("OK");
    
    String newFWVersion = httpClient.getString();

    newVersion = newFWVersion.toInt();  
    if( newVersion > FW_VERSION ) 
    {
      Serial.println("new ESP32 firmware v" + String(newVersion) + " available");
      fwURL.concat( "_v");
      fwURL.concat( newVersion );
      fwImageURL = fwURL;
      fwImageURL.concat( ".bin" );
      Serial.print( "firmware link: " );
      Serial.println(fwImageURL);
      httpClient.end();
    }
    else
    {
      Serial.println("current ESP32 firmware is up2date");
      httpClient.end();
      return -1;
    }
  }
  else
  {
    Serial.print("NOK");
    Serial.println( "Firmware version check failed, got HTTP response code: " );
    Serial.println( httpCode );
    Serial.println(fwVersionURL);
    httpClient.end();
    return -1;
  } 

  Serial.println( "Preparing ESP32 FW update..." );
//  Serial.println(fwImageURL);  

  if (wifi_client.connect(host.c_str(), port)) 
  {
    // Connection Succeed.
    // Fetching the bin
    String bin;
    bin.concat(urlPath);
    bin.concat(WiFi_hostname);
    bin.concat("_v");
    bin.concat(newVersion);
    bin.concat(".bin");
    
    Serial.println("Fetching Bin: " + String(host) + ":" + String(port) + String(bin));

    // Get the contents of the bin file
    wifi_client.print(String("GET ") + bin + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Cache-Control: no-cache\r\n" +
                 "Connection: close\r\n\r\n");

    // Check what is being sent
    //    Serial.print(String("GET ") + bin + " HTTP/1.1\r\n" +
    //                 "Host: " + host + "\r\n" +
    //                 "Cache-Control: no-cache\r\n" +
    //                 "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (wifi_client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Client Timeout !");
        wifi_client.stop();
        return -1;
      }
    }
    // Once the response is available,
    // check stuff

    /*
       Response Structure
        HTTP/1.1 200 OK
        x-amz-id-2: NVKxnU1aIQMmpGKhSwpCBh8y2JPbak18QLIfE+OiUDOos+7UftZKjtCFqrwsGOZRN5Zee0jpTd0=
        x-amz-request-id: 2D56B47560B764EC
        Date: Wed, 14 Jun 2017 03:33:59 GMT
        Last-Modified: Fri, 02 Jun 2017 14:50:11 GMT
        ETag: "d2afebbaaebc38cd669ce36727152af9"
        Accept-Ranges: bytes
        Content-Type: application/octet-stream
        Content-Length: 357280
        Server: AmazonS3
                                   
        {{BIN FILE CONTENTS}}
    */
    while (wifi_client.available()) {
      // read line till /n
      String line = wifi_client.readStringUntil('\n');
      // remove space, to check if the line is end of headers
      line.trim();

      // if the the line is empty,
      // this is end of headers
      // break the while and feed the
      // remaining `client` to the
      // Update.writeStream();
      if (!line.length()) {
        //headers ended
        break; // and get the OTA started
      }

      // Check if the HTTP Response is 200
      // else break and Exit Update
      if (line.startsWith("HTTP/1.1")) {
        if (line.indexOf("200") < 0) {
          Serial.println("Got a non 200 status code from server. Exiting OTA Update.");
          break;
        }
      }

      // extract headers here
      // Start with content length
      if (line.startsWith("Content-Length: ")) {
        contentLength = atoi((getHeaderValue(line, "Content-Length: ")).c_str());
        Serial.println("Got " + String(contentLength) + " bytes from server");
      }

      // Next, the content type
      if (line.startsWith("Content-Type: ")) {
        String contentType = getHeaderValue(line, "Content-Type: ");
        Serial.println("Got " + contentType + " payload.");
        if (contentType == "application/octet-stream") {
          isValidContentType = true;
        }
      }
    }
  } else {
    // Connect to S3 failed
    // May be try?
    // Probably a choppy network?
    Serial.println("Connection to " + String(host) + " failed. Please check your setup");
    // retry??
    // execOTA();
  }

  // Check what is the contentLength and if content type is `application/octet-stream`
  Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));

  // check contentLength and content type
  if (contentLength && isValidContentType) {
    // Check if there is enough to OTA Update
    bool canBegin = Update.begin(contentLength);

    // If yes, begin
    if (canBegin) {
      Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");
      // No activity would appear on the Serial monitor
      // So be patient. This may take 2 - 5mins to complete
      size_t written = Update.writeStream(wifi_client);

      if (written == contentLength) {
        Serial.println("Written : " + String(written) + " successfully");
      } else {
        Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?" );
        // retry??
        // execOTA();
      }

      if (Update.end()) {
        Serial.println("OTA done!");
        if (Update.isFinished()) {
          Serial.println("Update successfully completed. Rebooting.");
          ESP.restart();
        } else {
          Serial.println("Update not finished? Something went wrong!");
        }
      } else {
        Serial.println("Error Occurred. Error #: " + String(Update.getError()));
      }
    } else {
      // not enough space to begin OTA
      // Understand the partitions and
      // space availability
      Serial.println("Not enough space to begin OTA");
      wifi_client.flush();
    }
  } else {
    Serial.println("There was no content in the response");
    wifi_client.flush();
  }

}

 #endif 
 
