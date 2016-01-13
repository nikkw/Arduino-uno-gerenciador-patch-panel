#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "Main.h"

#define MAX_LINE 80
#define MAX_RESPONSE_SIZE 400

void ProcessClientMessage();

#define CODE_TURN_OFF_ALL_RELAYS       1
#define CODE_TURN_ON_ALL_RELAYS        2
#define CODE_REVERSE_RELAY_STATUS      3
#define CODE_CHANGE_IP                 4
#define CODE_CHANGE_GATEWAY            5
#define CODE_CHANGE_SUBNETWORK         6
#define CODE_CHANGE_PASS               7
#define CODE_LOGOFF                    8
#define CODE_SETTINGS				   9
#define CODE_RESTART  				   10


#define MAX_CODE 10

#endif