// Mouse Handler.h

#ifndef _MOUSE HANDLER_h
#define _MOUSE HANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define HIGH_THRESHOLD	600
#define LOW_THRESHOLD	350
#define HIGH_LATENCY	1100
#define LOW_LATENCY		100
	
#define MOUSERESOLUTION	50

long timerMouseClick;
long mouseTimer;

#define MOUSECLICKTIMEOUT	1000
#define MOUSESAMPLINGINTERVAL	100

void mouseCommand(uint8_t buttons, uint8_t x, uint8_t y) {
	Serial3.write(0xFD);
	Serial3.write((byte)0x00);
	Serial3.write((byte)0x03);
	Serial3.write(buttons);
	Serial3.write(x);
	Serial3.write(y);
	Serial3.write((byte)0x00);
	Serial3.write((byte)0x00);
	Serial3.write((byte)0x00);
}

uint8_t scanJoystickArrow(){
	uint8_t direction=0;

	#define HIGH_THRESHOLD	700
	#define LOW_THRESHOLD	300
	
	int temp=analogRead(RIGHT_VERTICAL);
	
	if(temp>HIGH_THRESHOLD){
		transmitSingle(KEY_ARROW_UP);
	}else if (temp<LOW_THRESHOLD){
		transmitSingle(KEY_ARROW_DOWN);
	}
	
	temp=analogRead(RIGHT_HORIZONTAL);
	
	if(temp>HIGH_THRESHOLD){
		transmitSingle(KEY_ARROW_RIGHT);
	}else if (temp<LOW_THRESHOLD){
		transmitSingle(KEY_ARROW_LEFT);
	}
	return direction;
	
}

void readMouseJoystick(){

	boolean changed=false;
	
	uint8_t x=0;
	uint8_t y=0;
	
	uint16_t temp=analogRead(LEFT_VERTICAL);
	
	if(temp>HIGH_THRESHOLD){
		y=(temp-HIGH_THRESHOLD)/MOUSERESOLUTION; // Get the difference between threshold and divide by resolution.
		changed=true;
		y=0-y;
	}else if (temp<LOW_THRESHOLD){
		y=(LOW_THRESHOLD-(uint8_t)temp)/MOUSERESOLUTION;
		changed=true;
	}
	
	temp=analogRead(LEFT_HORIZONTAL);
	
	if(temp>HIGH_THRESHOLD){
		x=(temp-HIGH_THRESHOLD)/MOUSERESOLUTION;
		changed=true;	
	}else if (temp<LOW_THRESHOLD){
		x=(LOW_THRESHOLD-(uint8_t)temp)/MOUSERESOLUTION;
		x=0-x;
		changed=true;
	}
	
	if(changed){
		mouseMove=true;
		timerMouseClick=millis();
		mouseCommand(0,x,y);
		delay(10);
	}
	
	if(millis()-timerMouseClick>MOUSECLICKTIMEOUT){
		mouseMove=false;
	}
	
}

void scanMouseJoystick(uint8_t samplingInterval){
	
	if(mouseMove){
		readMouseJoystick();
		Serial.println("Mouse");
	}
	
	if(millis()-mouseTimer>samplingInterval){
		readMouseJoystick();
		scanJoystickArrow();
		mouseTimer=millis();
	}	
	
}



#endif

