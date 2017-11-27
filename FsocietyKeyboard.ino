#include <Keypad.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

#include "FUNC_PROTOTYPE.h"
#include "CREDENTIALS.h"
#include "Pin_Config.h"
#include "Keymap.h"
#include "OLED_Handler.h"
#include "Keyboard_Handler.h"
#include "Mouse Handler.h"
#include "Applications.h"
#include "NFC_Handler.h"
#include "BLE_Handler.h"
#include "LED_Handler.h"

void setup(){

 Serial.begin(115200);
 Serial1.begin(115200);
 Serial2.begin(115200);  
 Serial3.begin(9600);	// UART to Bluefruit HID
 
 initOLED();
 initNFC();

}

void loop(){
	 
	uint8_t applicationCode=scanKeyboard();
	
	switch(applicationCode){
		case 0: break;
		case 1: commandMode();break;
	}
	
	getSamplingFrequency();
	scanMouseJoystick(100);
	scanNFC(1000);
	
}

