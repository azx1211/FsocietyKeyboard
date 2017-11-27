// Keyboard_Handler.h

#ifndef _KEYBOARD_HANDLER_h
#define _KEYBOARD_HANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

uint8_t GLOBALMODIFIER;
boolean HOLD_GLOBALMODIFIER;
#define MODIFIERBURSTDELAY	100
long timerModifierBurst;

#include "HID_Serial.h"

String msg;

unsigned long loopCount;
unsigned long startTime;
boolean idleStatus=true;

boolean mouseMove=false;

void mouseCommand(uint8_t buttons, uint8_t x, uint8_t y);

void checkMouseClick(uint8_t click){
	
	switch(click){
		case KEY_CONTROL_LEFT:
			mouseCommand(MOUSDE_LEFT_CLICK, 0, 0);
			delay(100);
		break;
		case KEY_ALT_LEFT:
			mouseCommand(MOUSDE_RIGHT_CLICK, 0, 0);
			delay(100);
		break;
	}
}

boolean isPrintableChar(uint8_t in){
	if(in>=0xE0 && in<=0xE7){
		return false;
	}else {
		return true;
	}
}

uint8_t scanKeyboard(){
	
	if(millis()-startTime>2000 && !idleStatus){
		idleMode();
		idleStatus=true;
		Serial.println("OUT");
		startTime=millis();
	}
	
	uint8_t appCode=0;

	uint8_t pressedBuffers[]={0,0,0,0,0,0}; // buffer array for the keys that are being pressed.
	
	// Check if there is any key is being pressed. otherwise skip.
	if (kpd.getKeys()){
		for (int i=0; i<LIST_MAX; i++){   // Scan the whole key buffers.
			if (kpd.key[i].stateChanged){ // Find the keys that only have changed state. 
				switch (kpd.key[i].kstate) {				
					case HOLD:	
					Serial.print("Hold No: ");
					Serial.println(HIDtoPrintableASCII(kpd.key[i].kchar));
						do{			
							kpd.getKeys();			
							if(isPrintableChar(kpd.key[i].kchar)){
								pressedBuffers[i]=kpd.key[i].kchar;
								keyCommand(0,pressedBuffers);
								delay(150); // Delay burst of HOLD key here.
							}else{
								pressedBuffers[i]=255;
								keyCommand(0,pressedBuffers);
								HOLD_GLOBALMODIFIER=true;
								break;
							}
						}while(kpd.key[i].kstate==HOLD);
					break;
					
					case PRESSED:
						Serial.print("Key No: ");
						Serial.println(HIDtoPrintableASCII(kpd.key[i].kchar));
						
						if(mouseMove){
							checkMouseClick(kpd.key[i].kchar);
						}else{
							pressedBuffers[i]=kpd.key[i].kchar;	
						}			
								
					break;			
					
					case RELEASED:
						if(!isPrintableChar(kpd.key[i].kchar)){
							HOLD_GLOBALMODIFIER=false;
						}
					break;				
				}		
			}		
		}
		
		// Check if first token is application key shortcut. If yes, then flag the code.
		if(pressedBuffers[0]==GOTOCOMMANDMODE){
			appCode=1;
		}
		
		keyCommand(0,pressedBuffers);
		typingText(pressedBuffers);
		
		if(idleStatus){
			display.stopscroll();
			delay(20);
			display.clearDisplay();
			delay(10);
			display.setCursor(0,0);
			idleStatus=false;
			Serial.println("IN");
		}
		
		delay(1);
		startTime=millis();
		if(!HOLD_GLOBALMODIFIER) keysUp();

	}
	
	
			
	if(HOLD_GLOBALMODIFIER && (millis()-timerModifierBurst>MODIFIERBURSTDELAY)){
		burstModifierOnly();
		timerModifierBurst=millis();
	}	
	return appCode;
}

void getSamplingFrequency(){
	loopCount++;
	if ( (millis()-startTime)>5000) {
		Serial.print(F("Sampling Freq = "));
		Serial.print(loopCount/5);
		Serial.println(" Hz");
		startTime = millis();
		loopCount = 0;
	}
}

#endif

