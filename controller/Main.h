#ifndef __MAIN_H__
#define __MAIN_H__

#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <string.h>

#include "IO.h"
#include "Relay.h"
#include "Arduino.h"
#include "Server.h"
#include "Client.h"
#include "Parser.h"
#include "View.h"
#include "Security.h"
#include "PushButton.h"

#define DEFAULT_SPEED 9600

void Main();

#endif