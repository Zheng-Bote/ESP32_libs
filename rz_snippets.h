/*
TITLE: 
	rz_snippets.h

BRIEF:
	header only library

DESC: 
	Arduino library for ESP32 with some system related functions
	* don't use, deprecated

SOURCE: 
	https://github.com/Zheng-Bote/esp32_libs

SYNTAX:
	#include "rz_snippets.h"

RETURN:
	void

HISTORY:
Version | Date       | Developer        | Comments
------- | ---------- | ---------------- | ---------------------------------------------------------------
0.0.1   | 2018-10-13 | RZheng           | created 

*/

#include "Arduino.h"

#ifndef rz_snippets
#define rz_snipptes

String rz_baseMac()
{
  uint64_t chipid;  
  char baseMacChr[18] = {0};

  chipid=ESP.getEfuseMac(); 
  Serial.printf("ESP32 Chip ID = %04X",(uint16_t)(chipid>>32));//print High 2 bytes
  Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.
  sprintf(baseMacChr, "%04X",(uint16_t)(chipid>>32));
  Serial.print("baseMac: ");
  Serial.println(baseMacChr);
  return String(baseMacChr);
}

char* rz_strToChar(String str) 
{
  int len = str.length() + 1;
  char* buf = new char[len];
  strcpy(buf, str.c_str());
  return buf;
}


#endif 
