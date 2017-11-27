// Pin_Config.h

#ifndef _PIN_CONFIG_h
#define _PIN_CONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Analog inputs pin.
#define LEFT_VERTICAL		A12  // higher bigger value.
#define LEFT_HORIZONTAL		A13  // Right bigger Value
#define RIGHT_VERTICAL		A14  // Higher bigger value
#define RIGHT_HORIZONTAL	A15  // Right bigger Value

#define NFC_SS_PIN 36
#define NFC_RST_PIN 35

#endif

