// OLED_Handler.h
#ifndef _OLED_HANDLER_h
#define _OLED_HANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);

uint8_t charCounter=0;
char typingBuffer[11];

byte typingMode(byte character){
	
	boolean visibleKey=false;
	
	if(character>=4 && character<=29){
		character+=61;	// Convert to ascii
		visibleKey=true;
		}else if( character>=30 && character<=38){
		character+=19;
		visibleKey=true;
		}else if (character==39){
		character=48;
		visibleKey=true;
	}
	
	if(visibleKey){
		display.setTextSize(2);
		display.write(character);
		display.display();
		return character;
		}else{
		return 0;
	}
}

void resetDisplayWithBuffer(){
	display.clearDisplay();
	display.setCursor(0,0);
	display.setTextSize(2);
	for(int i=1;i<11;i++){
		display.write(typingBuffer[i]);
	}
}

void typingText(byte *keyBuffers){
	// Display the typing on the OLED
	
		for(int s=0;s<6;s++){
			if(keyBuffers[s]!=0){
				
				if(charCounter++>20){
					resetDisplayWithBuffer();
					charCounter=11;	
				}
				
				if(charCounter>10){	
					byte temp=typingMode(keyBuffers[s]);
					if(temp!=0){
						typingBuffer[charCounter-10]=temp;
					}else{
						charCounter--;
					}
				}else{
					typingMode(keyBuffers[s]);
				}
				
				/* DEBUG
				Serial.print("CHARACTER: ");
				Serial.print((int)c);
				Serial.println();
				*/
							
			}	
		}
}


void idleMode(void) {
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(13,0);
	display.clearDisplay();
	display.print(F("   Keyboard   "));
	display.drawLine(0, 23, display.width()-1, 23, WHITE);
	display.setCursor(10,25);
	display.print("HID-BT-OK:WIFI-LORA-NO");
	display.setTextSize(2);
	display.setCursor(10,5);
	display.print("Sumas+a");
	//display.print("f/society");
	display.display();
	delay(1);
	
	display.startscrollleft(0x00, 0x0F);

}

void shortBlurb(String text, int timeout, boolean scroll){
	
	if(!scroll) display.stopscroll();

	display.clearDisplay();
	display.setCursor(0,0);
	display.setTextSize(2);
	display.print(text);
	display.display();
	
	if(timeout!=0){
		delay(timeout);
		idleMode();
	}
	
}

void initOLED(){
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	delay(10);
	display.clearDisplay();
	idleMode();
}

#endif

