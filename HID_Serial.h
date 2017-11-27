// HID_Serial.h

#ifndef _HID_SERIAL_h
#define _HID_SERIAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void burstModifierOnly(){
	// First byte identifier. a must.
	Serial3.write(0xFD);       // our command
		
	// Print modifier 
	Serial3.write((byte)GLOBALMODIFIER);  // modifier!
		
	//Splitter byte
	Serial3.write((byte)0x00); // 0x00
		
	// Send dummy 0x00 6 times.
	for(int i=0;i<6;i++){
		Serial3.write((byte)0x00);
	}
}

uint8_t checkModifiers(){
	
	if(!HOLD_GLOBALMODIFIER) GLOBALMODIFIER=0x00;
	
	// Scan the whole keys one time to check if any modifier are begin pressed.
	kpd.getKeys();
	
	for (int i=0; i<LIST_MAX; i++){  // Scan the whole key list. 		
		if (kpd.key[i].kstate==PRESSED || kpd.key[i].kstate==HOLD){
			switch(kpd.key[i].kcode){
				case 42: GLOBALMODIFIER|=MODIFIER_SHIFT_LEFT; break;
				case 53: GLOBALMODIFIER|=MODIFIER_SHIFT_RIGHT; break;
				case 56: GLOBALMODIFIER|=MODIFIER_CONTROL_LEFT; break;
				case 64: GLOBALMODIFIER|=MODIFIER_CONTROL_RIGHT; break;
				case 58: GLOBALMODIFIER|=MODIFIER_ALT_LEFT; break;
				case 62: GLOBALMODIFIER|=MODIFIER_ALT_RIGHT; break;
				case 57: GLOBALMODIFIER=MODIFIER_FN; break;
			}
			
			//Serial.print("Keymax: ");
			//Serial.println(LIST_MAX);
			
			// Clear the GUI modifier unless it is going to be used the comments below. 
			if(GLOBALMODIFIER!=MODIFIER_FN){
				
				bitClear(GLOBALMODIFIER,6);
				bitClear(GLOBALMODIFIER,3);
					
			}
			//Serial.println(GLOBALMODIFIER,BIN);			
		}
	}
	return GLOBALMODIFIER;
}

void keyCommand(uint8_t modifiers, uint8_t *keycode){
	
	// First byte identifier. a must.
	Serial3.write(0xFD);       // our command
	
	checkModifiers();
	modifiers=GLOBALMODIFIER;
		
	if(modifiers!=0x00){
		switch(modifiers){
			case MODIFIER_FN:
			if(keycode[0]!=0x00) keycode[0]+=28; // 28 is the difference between number 1 and F1'
			modifiers=0x00;
			break;
		}
	}
	
	// Print modifier
	Serial3.write(modifiers);  // modifier!
	
	//Splitter byte
	Serial3.write((byte)0x00); // 0x00
	
	// Prints byte 1 till 6 sequentially
	for(int i=0;i<6;i++){
		Serial3.write(keycode[i]);
	}
}


void singleKeyCommand(uint8_t keycode){
	uint8_t buf[]={keycode,0,0,0,0,0};
	keyCommand(0,buf);
}

void keysUp(){
	// First byte identifier. a must.
	Serial3.write(0xFD);       // our command
		
	// Print modifier
	Serial3.write((byte)0);  // modifier!
		
	//Splitter byte
	Serial3.write((byte)0x00); // 0x00
		
	// Prints byte 1 till 6 sequentially
	for(int i=0;i<6;i++){
		Serial3.write((byte)0x00);
	}
}

void transmitSingle(uint8_t code){
	// First byte identifier. a must.
	Serial3.write(0xFD); //our command
			
	// Print modifier
	Serial3.write((byte)checkModifiers()); 
			
	//Splitter byte
	Serial3.write((byte)0x00); //0x00
			
	Serial3.write((byte)code);
	for(int i=0;i<5;i++){
		Serial3.write((byte)0x00);
	}
		
	delay(5);	
	if(!HOLD_GLOBALMODIFIER) keysUp();
}

#endif

