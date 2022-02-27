/* RRBBP
 * 2018-10-28
 * v0.01
*/

#include "Arduino.h"

#ifndef rz_sim808
#define rz_sim808 


// #####
static char callerID1[] = "+4916xxxxxxxx"; // Sony XZ2c
static char callerID2[] = "+4916xxxxxxxx"; // Samsung S10
static char callerID3[] = "+4915xxxxxxxx"; // Xiaomi Mi Max3

// #####

#include "Adafruit_FONA.h"

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

char replybuffer[255];
HardwareSerial *fonaSerial = &Serial2;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);
char fonaNotificationBuffer[64];
char smsBuffer[250];

int rz_sim808_start()
{
  int counter = 0;
  int cLimit = 5;
  
  Serial.println(F("FONA SMS caller ID test"));
  Serial.println(F("FONA initializing....(May take 3 seconds)"));
  fonaSerial->begin(4800);

  while (! fona.begin(*fonaSerial)) 
  {
    Serial.println(F("Couldn't find FONA"));
    counter++;
    delay(2000);
    if(counter >= cLimit)
    {
      Serial.println("FAILED: FONA not found");
      return -1;      
    }
  }
  Serial.println(F("FONA is OK"));
  
  char imei[16] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("SIM card IMEI: "); Serial.println(imei);
  }

//
        // read the network/cellular status
        uint8_t n = fona.getNetworkStatus();
        Serial.print(F("Network status "));
        Serial.print(n);
        Serial.print(F(": "));
        if (n == 0) Serial.println(F("Not registered"));
        if (n == 1) Serial.println(F("Registered (home)"));
        if (n == 2) Serial.println(F("Not registered (searching)"));
        if (n == 3) Serial.println(F("Denied"));
        if (n == 4) Serial.println(F("Unknown"));
        if (n == 5) Serial.println(F("Registered roaming"));
//
  
  fonaSerial->print("AT+CNMI=2,1\r\n");  
  Serial.println("FONA Ready");
  return 0;
}

void rz_Fona_receive()
{
  char* bufPtr = fonaNotificationBuffer;    //handy buffer pointer
  
  if (fona.available())      //any data available from the FONA?
  {
    int slot = 0;            //this will be the slot number of the SMS
    int charCount = 0;
    //Read the notification into fonaInBuffer
    do  
    {
      *bufPtr = fona.read();
      Serial.write(*bufPtr);
      delay(1);
    } while ((*bufPtr++ != '\n') && (fona.available()) && (++charCount < (sizeof(fonaNotificationBuffer)-1)));
    
    //Add a terminal NULL to the notification string
    *bufPtr = 0;

    //Scan the notification string for an SMS received notification.
    //  If it's an SMS message, we'll get the slot number in 'slot'
    if (1 == sscanf(fonaNotificationBuffer, "+CMTI: " FONA_PREF_SMS_STORAGE ",%d", &slot)) 
    {
      Serial.print("slot: "); Serial.println(slot);
      
      char callerIDbuffer[32];  //we'll store the SMS sender number in here
      
      // Retrieve SMS sender address/phone number.
      if (! fona.getSMSSender(slot, callerIDbuffer, 31)) 
      {
        Serial.println("Didn't find SMS message in slot!");
      }
      Serial.print(F("FROM: ")); Serial.println(callerIDbuffer);

      //char callerID1[] = "+491622663867";
      //char callerID2[] = "+491622664071";
      if(strcmp(callerID1, callerIDbuffer) == 0 || strcmp(callerID2, callerIDbuffer) == 0 || strcmp(callerID3, callerIDbuffer) == 0 ) 
      {
        Serial.println("callerID ist gleich callerIDbuffer!");
        // Retrieve SMS value.
        uint16_t smslen;
        if (fona.readSMS(slot, smsBuffer, 250, &smslen)) 
        { // pass in buffer and max len!
          Serial.println(smsBuffer);
        }
        //Send back an automatic response
        Serial.println("Sending reponse...");
        char msg[160] = {0};
        if(strcmp(callerID1, callerIDbuffer) == 0)
        {
          strcpy(msg, "Hallo Sony");
        }
        else if(strcmp(callerID2, callerIDbuffer) == 0)
        {
          strcpy(msg, "Hallo Samsung");
        }
        else if(strcmp(callerID3, callerIDbuffer) == 0)
        {
          strcpy(msg, "Hallo Mi Max3");
        }
        if (!fona.sendSMS(callerIDbuffer, msg)) 
        {
          Serial.println(F("Failed"));
        }
        else 
        {
          Serial.println(F("Sent!"));
        }
        if(strcmp(smsBuffer, "Hallo von Sony") == 0) 
        {
          Serial.println("Msg : Hallo von Sony");
        }
        if(strcmp(smsBuffer, "HT open") == 0) 
        {
          Serial.println("Msg : Haustuer open");
          strcpy(msg, "Haustuer opne");
          strcpy(payload.sender, sender);
          strcpy(payload.receiver, "GW");
          strcpy(payload.type, "actor");
          strcpy(payload.phone, callerIDbuffer);
          strcpy(payload.msg, smsBuffer);
          rz_action_payload(&payload);
          
        }

Serial.println(F("### TEST Lora & MQTT###"));
rz_sendLora("1CC0", "T4", "{\"n\":\"sms\",\"d\":\"rec\"}");
rz_mqtt_sendMsg("Test", "SMS received");


        // rz_action_msg_rcv(String receiver, String command, String sendfrom, String datamsg)
        rz_action_msg_rcv(rz_baseMac(), "T3", "SMS", smsBuffer);
      }
      else
      {
        Serial.println("callerID ist NICHT gleich callerIDbuffer!");
      }      
      // delete the original msg after it is processed
      //   otherwise, we will fill up all the slots
      //   and then we won't be able to receive SMS anymore
      if (fona.deleteSMS(slot)) 
      {
        Serial.print(F("deleted SMS in slot ")); Serial.println(slot);
      }
      else 
      {
        Serial.print(F("Couldn't delete SMS in slot ")); Serial.println(slot);
        fona.print(F("AT+CMGD=?\r\n"));
      }
    }
  }  
}

#endif 
