#include "Client.h"

/*
rodar em todos ies
modo offline
*/

void ProcessClientMessage(){
	EthernetClient client = GetAvailableClient();	
	if(client){		

		String line1;

		for(byte i = 0; i < MAX_LINE; i++){
			char c = client.read();

			if(c == '\n'){
				break;
			}	

			line1 += c;
		}

		auto packetId = GetPacketId(line1);

		//in session packets
		if(packetId == CODE_TURN_OFF_ALL_RELAYS){
			TurnOffAllRelays();
			WriteResponse(client, true);	
		}

		else if(packetId == CODE_TURN_ON_ALL_RELAYS){
			TurnOnAllRelays();
			WriteResponse(client, true);	
		}
		
		else if(packetId == CODE_REVERSE_RELAY_STATUS){
			String arg = GetArgument(line1, 1);

			if(arg != ""){
				byte relayPos = arg.toInt();
				ReverseRelayStatus(relayPos);
				client.print(F("<script>window.location = '/';</script>"));				
			}
			else{
				Write404(client);
			}
		}

		else if(packetId == CODE_CHANGE_IP){
			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			String arg = GetArgument(plain, 0);

			String value1 = StringSplit(arg, '.', 0);
			String value2 = StringSplit(arg, '.', 1);
			String value3 = StringSplit(arg, '.', 2);
			String value4 = StringSplit(arg, '.', 3);

			if(value1.length() > 0 && value2.length() > 0 && value3.length() > 0 && value4.length() > 0){

				byte ip[4];
				memset(&ip, 0, sizeof ip);

				ip[0] = value1.toInt();
				ip[1] = value2.toInt();
				ip[2] = value3.toInt();
				ip[3] = value4.toInt();

				memcpy(Arduino.Ip, ip, sizeof Arduino.Ip);

				WriteConfigurations();	

				WriteResponse(client, true);					
			}
			else{
				WriteResponse(client, false);
			}
		}

		else if(packetId == CODE_CHANGE_GATEWAY){
			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			String arg = GetArgument(plain, 0);

			String value1 = StringSplit(arg, '.', 0);
			String value2 = StringSplit(arg, '.', 1);
			String value3 = StringSplit(arg, '.', 2);
			String value4 = StringSplit(arg, '.', 3);

			if(value1.length() > 0 && value2.length() > 0 && value3.length() > 0 && value4.length() > 0){

				byte ip[4];
				memset(&ip, 0, sizeof ip);

				ip[0] = value1.toInt();
				ip[1] = value2.toInt();
				ip[2] = value3.toInt();
				ip[3] = value4.toInt();

				memcpy(Arduino.Gateway, ip, sizeof Arduino.Gateway);

				WriteConfigurations();			

				WriteResponse(client, true);					
			}
			else{
				WriteResponse(client, false);
			}
		}

		else if(packetId == CODE_CHANGE_SUBNETWORK){
			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			String arg = GetArgument(plain, 0);

			String value1 = StringSplit(arg, '.', 0);
			String value2 = StringSplit(arg, '.', 1);
			String value3 = StringSplit(arg, '.', 2);
			String value4 = StringSplit(arg, '.', 3);

			if(value1.length() > 0 && value2.length() > 0 && value3.length() > 0 && value4.length() > 0){

				byte ip[4];
				memset(&ip, 0, sizeof ip);

				ip[0] = value1.toInt();
				ip[1] = value2.toInt();
				ip[2] = value3.toInt();
				ip[3] = value4.toInt();

				memcpy(Arduino.SubNetwork, ip, sizeof Arduino.SubNetwork);

				WriteConfigurations();		

				WriteResponse(client, true);	
			}
			else{
				WriteResponse(client, false);
			}
		}

		else if(packetId == CODE_CHANGE_PASS){
			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			String oldPass = GetArgument(plain, 0);
			String newPass1 = GetArgument(plain, 1);
			String newPass2 = GetArgument(plain, 2);	

			if(oldPass == Arduino.Pass){
				if(newPass1 == newPass2){
					if(newPass1.length() >= 4 && newPass1.length() <= sizeof Arduino.Pass){				
						
						char pass[sizeof Arduino.Pass];
						memset(pass, 0, sizeof pass);
						newPass1.toCharArray(pass, newPass1.length() + 1);
						
						strncpy(Arduino.Pass, pass, sizeof Arduino.Pass); 

						WriteConfigurations();

						WriteResponse(client, true);
					}
					else{
						WriteResponse(client, false);
 					}
				}
				else{
					WriteResponse(client, false);
				}
			}
			else{
				WriteResponse(client, false);
			}			
		}
		
		else if(packetId == CODE_LOGOFF){
			WriteLogoff(client);
		}

		else if(packetId == CODE_SETTINGS){
			WriteSettings(client);
		}

		else if(packetId == CODE_RESTART){
			client.print(F("<script>window.location = '/';</script>"));
			RestartServer();
		}

		else if(packetId > MAX_CODE){
			Write404(client);
		}

		else{ //off session packets		

			String response;
			static const String match = F("Authorization: Basic");
			bool flag = false;
			uint16_t index = 0;
			uint16_t final = 0;

			for(uint16_t i = 0; i < MAX_RESPONSE_SIZE; i++){
				char c = client.read();

				response += c;

				if(response.indexOf(match) >= 0 && !flag){
					flag = true;
					index = i+2;
				}

				if(flag && c == '\n'){
					final = i;
					break;
				}
			}

			if(index > 0 && final > 0 && flag){
				String hash = response.substring(index, final);

				String dec = b64_decode_string(hash);

				String arduino = String(Arduino.User) + ":" + String(Arduino.Pass);
				
				if(dec == arduino){
					WriteMainPage(client);
				}
				else{
					WriteLoginRequest(client);
				}
			}
			else{
				WriteLoginRequest(client);
			}
		}

		delay(1);
		client.stop();	
	}
}
