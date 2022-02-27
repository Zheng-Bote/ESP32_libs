/* RRBBP
 * 2018-11-02
 * v0.01
*/

#include "Arduino.h"

#ifndef rz_aes


#include <Crypto.h>
#include "base64.hpp"
#include "esp_system.h"

#define VERSION 1
#define BLOCK_SIZE 16

uint8_t key[BLOCK_SIZE] = { 0x1C,0x3E,0x4B,0xAF,0x13,0x4A,0x89,0xC3,0xF3,0x87,0x4F,0xBC,0xD7,0xF3, 0x31, 0x31 };
uint8_t iv[BLOCK_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


void bufferSize(char* text, int &length)
{
  int i = strlen(text);
  int buf = round(i / BLOCK_SIZE) * BLOCK_SIZE;
  length = (buf <= i) ? buf + BLOCK_SIZE : length = buf;
  //length = (buf <= i) ? buf + BLOCK_SIZE : buf;
}
    
void encrypt(char* plain_text, char* output, int length)
{
  byte enciphered[length];
  RNG::fill(iv, BLOCK_SIZE); 
  AES aesEncryptor(key, iv, AES::AES_MODE_128, AES::CIPHER_ENCRYPT);
  aesEncryptor.process((uint8_t*)plain_text, enciphered, length);
  int encrypted_size = sizeof(enciphered);
  char encoded[encrypted_size];
  encode_base64(enciphered, encrypted_size, (unsigned char*)encoded);
  strcpy(output, encoded);
}

void decrypt(char* enciphered, char* output, int length)
{
  length = length + 1; //re-adjust
  char decoded[length];
  decode_base64((unsigned char*)enciphered, (unsigned char*)decoded);
  bufferSize(enciphered, length);
  byte deciphered[length];
  AES aesDecryptor(key, iv, AES::AES_MODE_128, AES::CIPHER_DECRYPT);
  aesDecryptor.process((uint8_t*)decoded, deciphered, length);
  strcpy(output, (char*)deciphered);
}

void decryptMsg(char* encrypted) 
{
  int length = 0;
  length = strlen(encrypted);
  char decrypted[length];
  decrypt(encrypted, decrypted, length);

  Serial.print("Decrypted: ");
  Serial.println(decrypted);
}

char encryptMsg(char* plain_text) 
{
  int length = 0;
  bufferSize(plain_text, length);

  char encrypted[length];
  encrypt(plain_text, encrypted, length);

  Serial.print("Encrypted: ");
  Serial.println(encrypted); 
  
  decryptMsg(encrypted);
  return *encrypted;
}


#endif 
