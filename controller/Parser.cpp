#include "Parser.h"

String StringIntersection(String response, char cIndex, char cFinal){
	byte index = response.indexOf(cIndex);
	byte final = response.indexOf(cFinal);

	if(index >= 0 && final >= 0){
		return response.substring(index+1, final);	
	}

	return "";	
}

String StringSplit(String data, char separator, byte index){
	byte found = 0;
  	char strIndex[] = {0, -1};
  	byte maxIndex = data.length()-1;

  	for(byte i = 0; i <= maxIndex && found <= index; i++){
  		if(data.charAt(i) == separator || i == maxIndex){
        	found++;
        	strIndex[0] = strIndex[1]+1;
        	strIndex[1] = (i == maxIndex) ? i + 1 : i;
    	}
  	}

  	return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

byte GetPacketId(String line){
	String intersection = StringIntersection(line, '[', ']');

	if(intersection != ""){
		byte argumentCount = 0;

		for(byte i = 0; i < intersection.length(); i++){
			if(intersection.charAt(i) == ';'){
				argumentCount ++;
			}
		}

		if(argumentCount == 0){
			return intersection.toInt();
		}

		String split = StringSplit(intersection, ';', 0);

		if(split != ""){
			return split.toInt();
		}
	}	

	return 0;
}

String GetArgument(String line, byte arg){
	String intersection = StringIntersection(line, '[', ']');

	if(intersection != ""){
		byte argumentCount = 0;

		for(byte i = 0; i < intersection.length(); i++){
			if(intersection.charAt(i) == ';'){
				argumentCount ++;
			}
		}

		if(arg <= argumentCount){
			String split = StringSplit(intersection, ';', arg);
			
			if(split != ""){
				return split;
			}
		}
	}	

	return "";
}