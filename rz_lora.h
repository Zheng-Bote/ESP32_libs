/* RRBBP
* 2019-10-06
* v0.03
* last change: Lora receive
*/

#include "Arduino.h"

#include <xxtea-iot-crypt.h>

#ifndef rz_lora
#define rz_lora

// https://www.arduinolibraries.info/libraries/xxtea-iot-crypt
// https://github.com/boseji/xxtea-lib
#include <xxtea-iot-crypt.h>

// ##### 
#define SS 18
#define RST 14
#define DI0 26
#define BAND 868.00
#define spreadingFactor 6
#define SignalBandwidth 125000
#define preambleLength 8
#define codingRateDenominator 5
// char sender[4] = "i01";
char* sender = rz_strToChar(rz_baseMac());
// #####

#include <LoRa.h>


int rz_lora_start()
{
  LoRa.setPins(SS,RST,DI0);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

 LoRa.setSyncWord(0xF3); // ranges from 0-0xFF, default 0x34

  Serial.print("LoRa Spreading Factor: ");
  Serial.println(spreadingFactor);
  LoRa.setSpreadingFactor(spreadingFactor);
  
  Serial.print("LoRa Signal Bandwidth: ");
  Serial.println(SignalBandwidth);
  LoRa.setSignalBandwidth(SignalBandwidth);

  LoRa.setCodingRate4(codingRateDenominator);

  LoRa.setPreambleLength(preambleLength);
  
  Serial.println("LoRa Initial OK!");
}

void rz_sendLora(char receiver[4], char command[3], char msg[32])
{
  char msgtxt[50] = {0};

  strcat(msgtxt, receiver);
  strcat(msgtxt, "|");
  strcat(msgtxt, sender);
  strcat(msgtxt, "|");
  strcat(msgtxt, command);
  strcat(msgtxt, "|");
  strcat(msgtxt, msg);

  Serial.print("Lora sending Msg: ");
  Serial.println(msgtxt);

//
  String plaintext = F("Hi There we can work with this");

  // Set the Password
  xxtea.setKey("2Hot4U maybe");

  // Perform Encryption on the Data
  Serial.print(F(" Encrypted Data: "));
  String result = xxtea.encrypt(msgtxt);
  result.toLowerCase(); // (Optional)
  Serial.println(result);

  LoRa.beginPacket();
  LoRa.print(result);
  LoRa.endPacket(); 
//
  // send packet
//  LoRa.beginPacket();
//  LoRa.print(msgtxt);
//  LoRa.endPacket(); 
}

void rz_receiveLora(int packetSize) 
{
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  String incoming = "";
 
  while (LoRa.available()) 
  {
    incoming += (char)LoRa.read();
  }

  Serial.println("\n##########\nMessage: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println("\n##########\n");

  //
  xxtea.setKey("2Hot4U maybe");
  Serial.print("Decrypt: ");
  // OK: Serial.println(xxtea.decrypt(incoming));

  char *token, *string;
  string = rz_strToChar(xxtea.decrypt(incoming));
  Serial.println(string);
  
  int count = 0;
  boolean myMsg = false;
  String receiver, sendfrom, command, msgjson;
  
  while ((token = strsep(&string, "|")) != NULL)
  {
      Serial.println("##token##");
      Serial.println(token);
      if(count == 0 && strcmp(token, sender) == 0)
      {
        Serial.println("\n\t##payload for me ##");  
        myMsg = true;
     }
    if(myMsg == true)
    {

      /*
      if(count == 0) {Serial.print("0 Receiver: "); strcpy(receiver, token); Serial.println(token);}
      if(count == 1) {Serial.print("1 Sender "); strcpy(sendfrom, token);Serial.println(token);}
      if(count == 3) {Serial.print("3 msg "); Serial.println(token); strcat(msgjson, token); break;}
      */

      switch(count) 
        {
          case 0: {Serial.print("0 Receiver: "); receiver = String(token); Serial.println(token); break; }
          case 1: {Serial.print("1 Sender "); sendfrom = String(token); Serial.println(token); rz_sendLora(rz_strToChar(sendfrom), "T4", "{\"n\":\"LoRa\",\"d\":\"rec\"}"); rz_mqtt_sendMsg("C1FE/Test", "LoRa rec"); break;}
          case 2: {Serial.print("2 cmd "); command = String(token); Serial.println(token); break;}
          case 3: {Serial.print("3 msg "); msgjson = String(token); Serial.println(token); break;} 
          default: {Serial.println("irgendwas"); Serial.println(count);break;}
        }
     }
    else
    {
      Serial.println("Not my Msg");
      return;
    }
     count++; 
  }
  /*
   Serial.println("\t### LORA ###");
    Serial.print("Receiver: ");
    Serial.println(receiver);    
    Serial.print("Sender: ");
    Serial.println(sendfrom);
    Serial.print("command: ");
    Serial.println(command);    
    Serial.print("MSG JSON: ");
    Serial.println(msgjson);
 */
  rz_action_msg_rcv(receiver, command, sendfrom, msgjson);
}

#endif 
  
