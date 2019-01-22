/*
	Name:       DebugHelper.h
	Created:	12/01/2019
	Author:     master
	Version:	1.0.1
*/

#pragma once
#define DEBUG_HELPER

// Comment this line to don't show DEBUG output
#define DEBUG_ON
// Comment this line to don't show [millis] in DEBUG lines
//#define DEBUG_TIME_MILLIS
// Comment this line to don't sow a prefix on each line
// Define any prefix you want to be displayed 
//#define DEBUG_PREFIX	"<DEBUG>"

#include <stdarg.h>

char tmpStr[15];
#define DEBUG_D2STR(num, n, d)		(dtostrf(num, n, d, tmpStr))

#ifdef __AVR__
void SerialPrintf(char *fmt, ...) {
	char buffer[128];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, 128, fmt, args);
	va_end(args);
	Serial.print(buffer);
}

void SerialPrintf_P(const char *fmt, ...) {
	char buffer[128];
	va_list args;
	va_start(args, fmt);
	vsnprintf_P(buffer, 128, (const char *)fmt, args);
	va_end(args);
	Serial.print(buffer);
}
#endif

#ifdef DEBUG_PREFIX
#ifdef __AVR__
#define DEBUG_PRE1	SerialPrintf("%s ", DEBUG_PREFIX); 
#else  
#define DEBUG_PRE1	Serial.printf("%s ", DEBUG_PREFIX); 
#endif // __AVR__
#else
#define DEBUG_PRE1
#endif

#ifdef DEBUG_TIME_MILLIS
#ifdef __AVR__
#define DEBUG_PRE2	SerialPrintf("[%lu] ", millis());
#else
#define DEBUG_PRE2	Serial.printf("[%lu] ", millis());
#endif // __AVR__
#else
#define DEBUG_PRE2
#endif

#ifdef DEBUG_ON
#	ifdef __AVR__
#define DEBUG_PRINT(fmt, ...) \
	{ \
		DEBUG_PRE1 \
		DEBUG_PRE2 \
		SerialPrintf(fmt, __VA_ARGS__); \
	}
#define DEBUG_PRINT_P(fmt, ...) \
	{ \
		DEBUG_PRE1 \
		DEBUG_PRE2 \
		SerialPrintf_P(fmt, __VA_ARGS__); \
	}	
#	else // __AVR__
#define DEBUG_PRINT(...) \
	{ \
		DEBUG_PRE1 \
		DEBUG_PRE2 \
		Serial.printf(__VA_ARGS__); \
	}
#define DEBUG_PRINT_P(...) \
	{ \
		DEBUG_PRE1 \
		DEBUG_PRE2 \
		Serial.printf_P(__VA_ARGS__); \
	}
#endif // __AVR__
#else
#define DEBUG_PRINTLN(x) 
#define DEBUG_PRINT(x)
#endif