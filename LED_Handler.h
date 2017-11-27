// LED_Handler.h

#ifndef _LED_HANDLER_h
#define _LED_HANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define BURSTTIME	5

void changeLEDShow(byte code){
	for(int i=0;i<BURSTTIME;i++){
		Serial1.print("R");
		Serial1.print(code);
		Serial1.println("G"); 
		delay(10);
	}
}

#endif

