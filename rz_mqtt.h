/*
LIB: 
  rz_mqtt.h
DESC: 
  Arduino library for ESP32, with some MQTT client functionalities (publish, subscribe)

DEPENDENCIES:
  PubSubClient
  
SOURCE: 
  https://github.com/Zheng-Bote/ESP32_libs

Topic begins allways with ESP32/ESP32-<Chip-ID> where "Chip-ID" = Mac-Address

publishing:
  ESP32/ESP32-<Chip-ID>/status  // NTP time during boot/setup
  ESP32/ESP32-<Chip-ID>/temperature
  ESP32/ESP32-<Chip-ID>/humidity

subscribing:
  ESP32/ESP32-<Chip-ID>/get_temperature
  ESP32/ESP32-<Chip-ID>/get_humidity

Version | Date       | Developer  | Comments
------- | ---------- | ---------- | ---------------------------------------------------------------
0.1.0   | 2019-10-27 | RZheng     | created
0.4.0   | 2022-03-26 | RZheng     | baseMac removed 
1.0.0   | 2022-02-27 | RZheng     | some small corrections and code updates; finalized

*/

#ifndef rz_mqtt
#define rz_mqtt

#include "Arduino.h"
#include <WiFiClient.h>
#include <PubSubClient.h>


WiFiClient wifiClient;
PubSubClient mqtt_client(wifiClient);


int rz_mqttclient_start(std::string hostId)
{
  int counter = 0;
  int cLimit = 3;
  mqtt_client.setServer(mqttServer, mqttPort);
  while (!mqtt_client.connected()) 
  {
      //Serial.print("Connecting to MQTT...");
   
      if (mqtt_client.connect(hostId.c_str(), mqttUser, mqttPwd )) 
      {
           Serial.println("-- connected");
           return 0;
      } 
      else 
      {
        counter++;
        Serial.print("failed with state ");
        Serial.println(mqtt_client.state());
        delay(2000);
      }
      if(counter >= cLimit)
      {
        Serial.println("-- FAILED: MQTT connect impossible");
        return -1;      
      }
   }
}

bool rz_mqtt_sendMsg(std::string mqtt_topic, char mqtt_msg[])
{
  if (! mqtt_client.connect("nodeid", mqttUser, mqttPwd)) {
    rz_mqttclient_start("nodeid");
  }
  
  //char mqtt_topicStr[50];
  char mqtt_topicStr[100] = "ESP32/";
  //strcpy(mqtt_topicStr, mqtt_topic.c_str());
  strcat(mqtt_topicStr, mqtt_topic.c_str());

  //Serial.print("MQTT Message:\nTopic: ");
  //Serial.println(mqtt_topicStr);
  //Serial.print("Message: ");
  //Serial.println(mqtt_msg);
    
    if (mqtt_client.publish(mqtt_topicStr, mqtt_msg) == true) 
    {
      //Serial.println("MQTT successfully sent message");
      return true;
    } 
    else 
    {
      //Serial.println("MQTT error sending message");
      return false;
    }
}

void rz_mqtt_action(char* topic, char* msg)
{
  if(strcmp(topic, "C4D9/Alarm") == 0) 
  {
    Serial.println("Topic identical");
  }
  else
  {
    Serial.println("Topic not identical");
  }

  char delimiter[] = "/";
  char *ptr;
  char buf[50] = {0}; 
  ptr = strtok(topic, delimiter);
  while(ptr != NULL) 
  {
    strcpy(buf, ptr);
    
    printf("Abschnitt gefunden: %s\n", ptr);
    // naechsten Abschnitt erstellen
    ptr = strtok(NULL, delimiter);
  }

  Serial.print("Buffer: ");
  Serial.println(buf);

  
  typedef struct 
  {
    char type[50];
    char msgtxt[255];
    char action[100];
    int number;
  } Actions;
  
  Actions Action[2];

  strcpy(Action[0].type, "C4D9/Pushover");
  strcpy(Action[0].action, "Pushover");
  Action[0].number = 0;

  strcpy(Action[1].type, "C4D9/Alarm");
  strcpy(Action[1].action, "Alarm");
  Action[1].number = 1;

  Serial.print("Struct type: ");
  Serial.println(Action[1].type);

  int nr;
  for(int i = 0; i < 2; i++)
  {
    if(strcmp(Action[i].action, buf) == 0) 
    {
      nr = Action[i].number;
    }
  }

  switch(nr)
  {
    case 0: Serial.print("case 0: "); Serial.println(Action[nr].type); break;
    case 1: Serial.print("case 1: "); Serial.println(Action[nr].type); break;
    default: Serial.println("nr ist irgendwas\n"); break;
  }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
  char* buf = new char[length]; 

  Serial.print("\n");
  Serial.print("MQTT Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("MQTT Message (length: ");
  Serial.print(length);
  Serial.println("):");
    
  for (int i = 0; i < length; i++) 
  {
    Serial.print("-");
  }
  Serial.print("\n");

  strncat(buf, (char*)payload,length);
  Serial.println(buf);

  // Action
  //rz_action(topic, buf);
  //rz_action_msg_rcv(rz_baseMac(), topic, "MQTT", buf);
}

void rz_mqtt_subscribe(char mqtt_topic[])
{
    mqtt_client.setCallback(mqtt_callback);
    mqtt_client.subscribe(mqtt_topic);    
}

#endif 


 /********************** README *********************
 
 ### ESP32 Main =>


#include "rz_wifi.h"
#include "rz_snippets.h"
#include "rz_mqtt.h"

void setup()
{
    Serial.begin(115200);
    delay(10);

    rz_baseMac();
    rz_wifi_connect();
    rz_mqttclient_start();

    rz_mqtt_sendMsg("ESP32/Test", "Hello World");   // will be topic: <baseMac>/ESP32/Test
    rz_mqtt_subscribe("C4D9/Test");
    rz_mqtt_subscribe("C4D9/Alarm");
}



void loop()
{
    mqtt_client.loop();
}

### MQTT Client <= 

*/
