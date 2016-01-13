#ifndef __PARSER_H__
#define __PARSER_H__

#include "Main.h"

String StringIntersection(String response, char cIndex, char cFinal);
String StringSplit(String data, char separator, byte index);
byte GetPacketId(String line);
String GetArgument(String line, byte arg);

#endif
