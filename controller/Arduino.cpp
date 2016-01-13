#include "Arduino.h"

st_Arduino Arduino;

void InitializeArduino(){
	memset(&Arduino, 0, sizeof(Arduino));	
	ReadConfigurations();
}

void SetDefaultConfigurations(){
	st_Arduino p;
	memset(&p, 0, sizeof(p));

	strncpy(p.User, DEFAULT_USER, sizeof(p.User));
  	strncpy(p.Pass, DEFAULT_PASS, sizeof(p.Pass)); 

  	memcpy_P(&p.Ip[0], &DEFAULT_IP[0], sizeof(p.Ip));
  	memcpy_P(&p.Gateway[0], &DEFAULT_GATEWAY[0], sizeof(p.Gateway));
  	memcpy_P(&p.SubNetwork[0], &DEFAULT_SUBNETWORK[0], sizeof(p.SubNetwork));
  	memcpy_P(&p.Mac[0], &DEFAULT_MAC[0], sizeof(p.Mac));

  	eewrite(0, p);
}

void WriteConfigurations(){
	eewrite(0, Arduino);
}

void ReadConfigurations(){
	eeread(0, Arduino);
}

String GetIpStr(byte *ip){
	return (String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]));
}