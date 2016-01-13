#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include "Main.h"

#define DEFAULT_USER "admin"
#define DEFAULT_PASS "admin"
static const byte DEFAULT_IP[4] PROGMEM = {192, 168, 115, 177};
static const byte DEFAULT_GATEWAY[4] PROGMEM = {192, 168, 115, 253};
static const byte DEFAULT_SUBNETWORK[4] PROGMEM = {255, 255, 255, 0};
static const byte DEFAULT_MAC[6] PROGMEM = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

typedef struct {  
  char User[16];
  char Pass[16];
  byte Ip[4];  
  byte Gateway[4];  
  byte SubNetwork[4];  
  byte Mac[6];  
} st_Arduino;

extern st_Arduino Arduino;

void InitializeArduino();
void SetDefaultConfigurations();
void WriteConfigurations();
void ReadConfigurations();
String GetIpStr(byte *ip);

#endif