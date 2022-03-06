/*
TITLE: 
	rz_action.h

BRIEF:
	header only library

DESC: 
	Arduino library for ESP32, just provides some (LOra) functions
	* don't use, deprecated

SOURCE: 
	https://github.com/Zheng-Bote/esp32_libs

SYNTAX:
	#include "rz_action.h"

RETURN:
	void

HISTORY:
Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.0.1   | 2019-10-05 | RZheng           | created 
0.0.2   | 2019-10-06 | RZheng           | added: rz_action_msg_rcv()

*/

#include "Arduino.h"
#include <ArduinoJson.h>

#ifndef rz_action
#define rz_action

// Sender / Receiver
// 0 = Dragino GW, 1 = Congstar,
static int senderArr[2] = {0, 1};

// sender , receiver
// ogw1 (output GW 0), igw1 (input GW 0), 1099 | BC91 ... 
// char sender[4], char receiver[4], char command[3], char msg[32] char datamsg[50]

// command
// T0, T1, T2, T3, T4, T5
// 0 = Alarm, 1 = Sensor, 2 = Presence, 3 = Actor, 4 = Tester, 5 = System
static int typeArr[5] = {0, 1, 2, 3, 4};

// Mobile phone
// char callerID1[] = "+49162xxxx"; char callerID2[] = "+49162xxxxx";
// callerID1 = Sony , callerID2 = Samsung

// Name
static char nameID1[] = "RZheng", nameID2[] = "MZheng";


// #################################################

struct payloadMsg 
{
  char sender[50];
  char receiver[50];
  char type[20];
  char msg[32];
  char phone[32];
  char fullname[7];
};
//payload = {0,0,0,0,0};
struct payloadMsg payload;

// rz_action_payload(&payload);

void rz_action_payload(struct payloadMsg *payload)
{


// Zugriff auf die Elemente
//payload->fullname="111111";
//strcpy(payload.sender, "Dragino GW");

Serial.print("Name: ");
Serial.println(payload->sender);
Serial.println(payload->receiver);
Serial.println(payload->type);
Serial.println(payload->phone);
Serial.println(payload->msg);
//rz_sendLora("i00", "T3", payload->msg);

/*
  int i = actionArr[0];
  
  switch(i) 
  {
    case 0: Serial.println("null\n"); break;
    case 1: Serial.println("eins\n"); break;
    case 2: printf("zwei\n"); break;
    case 3: printf("drei\n"); break;
    default: printf("irgendwas\n"); break;
  }
*/
} 


void rz_action_msg_rcv(String receiver, String command, String sendfrom, String datamsg)
{

  // JSON
  
  StaticJsonDocument<200> doc;
  //char json[] = "{\"n\":\"gps\",\"d\":\"Hello World\"}";
  DeserializationError error = deserializeJson(doc, datamsg);
  
  // Test if parsing succeeds.
  if (error) 
  {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      //return;
  }

  int len = receiver.length() + 1;
  char* buf = new char[len];
  strcpy(buf, receiver.c_str());

  // => zuerst Abfrage nach command Typ
  
  //if(strcmp(buf), "1099") == 0)
  if (receiver.equals("1099") != 0)
  {
    Serial.print("Receiver: ");
    Serial.println(receiver);
    const char* sensor = doc["n"];
    const char* daten = doc["d"];
    Serial.println("Data:");
    Serial.println(sensor);
    Serial.println(daten);
    // OK:   rz_pcf8574_setPin(2, "on");
  }
  else if(receiver.equals("0C27") != 0)
  {
    Serial.println("\t => Msg for me");
    if(command.equals("0C27/T5") != 0)
    {
      Serial.print("\t\tCommand: ");
      Serial.println(command);
      if(datamsg.equals("status") != 0)
      {
        Serial.print("\t\tMsg status: ");
        Serial.println(datamsg);
      }
      if(datamsg.equals("update") != 0)
      {
        Serial.print("\t\tMsg update: ");
        Serial.println(datamsg);
      }      
    }
  }
  else
  {
    Serial.println("Nope: ");
    Serial.print("Receiver: ");
    Serial.println(receiver);    
    Serial.print("Sender: ");
    Serial.println(sendfrom);
  }
}

 #endif 
