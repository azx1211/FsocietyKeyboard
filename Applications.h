// Applications.h

#ifndef _APPLICATIONS_h
#define _APPLICATIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void changeLEDShow(byte code);

#define DEFAULT_LEDSHOW	3

/*
Command mode
*/
void commandMode(){

	shortBlurb(F("  COMMAND     MODE"),0,true);
	changeLEDShow(9);
	uint8_t selectedMode=DEFAULT_LEDSHOW;
		
	while(1){
		if(kpd.getKeys()){
			if (kpd.key[0].stateChanged){
				if(kpd.key[0].kstate==PRESSED){	
					
					if(kpd.key[0].kcode==61){
						Serial.println(F("EXIT"));
						changeLEDShow(selectedMode); //Change to selected mode before exiting the Command mode.
						break;		
					}
					
					if(kpd.key[0].kcode<10){
						selectedMode=kpd.key[0].kcode;
						changeLEDShow(selectedMode);
					}
					
				}
			}
	
		}
	}
	idleMode();
}

#endif

