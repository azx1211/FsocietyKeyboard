// BLE_Handler.h

#ifndef _BLE_HANDLER_h
#define _BLE_HANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define BLE_TIMEOUT	5000

void BLESerialHandler(){
	// read from port 1, send to port 0:
	if (Serial2.available()) {
		int inByte = Serial2.read();
		Serial.write(inByte);
	}

	// read from port 0, send to port 1:
	if (Serial.available()) {
		int inByte = Serial.read();
		Serial2.write(inByte);
		Serial1.write(inByte);
	}
	
	// read from port 1, send to port 0:
	if (Serial1.available()) {
		int inByte = Serial1.read();
		Serial.write(inByte);
	}
}

void connectBluetooth(){
	shortBlurb(F("Checking connection"),0,false);
	while(!Serial2.find("OK")){
		delay(300);
		Serial2.println("AT");
	}
	shortBlurb(F("Scanning for Bluetooth"),0,false);
	Serial2.println("AT+INQ");
	while(!Serial2.find("Devices Found"));
	shortBlurb(F("Device Found"),0,false);
	shortBlurb(F("Attempting to Connect"),0,false);
	Serial2.println("AT+CONN1");	//Connect to the first device found for now. 
	
	boolean connected=false;
	long counter=millis();	
	
	while(millis()-counter<5000){
		if(Serial2.find("Connected")){
			shortBlurb(F("CONNECTED"),2000,false);
			connected=true;
			break;
		}
	}
	
	if(!connected)shortBlurb(F("Failed Connection"),2000,false);
	commandMode();
}

#endif

