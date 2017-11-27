// NFC_Handler.h

#ifndef _NFC_HANDLER_h
#define _NFC_HANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

MFRC522 rfid(NFC_SS_PIN, NFC_RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

long intervalNFCScan;

void masterKeyRoutine(){
	shortBlurb(F("   Master    Key"), 0, true);
	
	for(int i=0;i<15;i++){
		Serial1.println("R8G");
		delay(10);
	}
	
	long masterKeyTimeout=millis();
	while(millis()-masterKeyTimeout<5000){
		kpd.getKeys();
		if (kpd.key[0].stateChanged){
			if(kpd.key[0].kstate==PRESSED){
				Serial3.print(ps[kpd.key[0].kcode]);
				
			}
		}
	}

	for(int i=0;i<15;i++){
		Serial1.println("R3G");
		delay(10);
	}

	idleMode();
}

void checkUid(byte *buffer, byte bufferSize){	

	boolean keyValid=true;
	
	for(int i=0;i<4;i++){
		if(masterRing[i]!=buffer[i]){
			keyValid=false;
			Serial.println("ERROR");
			break;
		}
	}
	
	if (keyValid){
		Serial.println("MATCH");
		masterKeyRoutine();
	}
}

void initNFC(){
	
	// PULL up the CS of the LORA pin, otherwise screwing up the SPI bus. 
	pinMode(8,OUTPUT);
	digitalWrite(8,HIGH);
	
	SPI.begin(); // Init SPI bus
	rfid.PCD_Init(); // Init MFRC522
	intervalNFCScan=millis();
}

void scanNFC(uint16_t interval){
	if(millis()-intervalNFCScan>interval){
		if (rfid.PICC_IsNewCardPresent()){
			// Verify if the NUID has been readed
			if ( ! rfid.PICC_ReadCardSerial())
			return;
			Serial.print(F("UID type: "));
			MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
			checkUid(rfid.uid.uidByte, rfid.uid.size);
		}
		intervalNFCScan=millis();
	}
}

#endif

