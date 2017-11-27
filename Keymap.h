// Keymap.h

#ifndef _KEYMAP_h
#define _KEYMAP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

#include "HID_Table.h"

// Keyboard MAP
const byte ROWS = 5; //four rows
const byte COLS = 14; //three columns

char keys[ROWS][COLS] = {
	{KEY_ESCAPE,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,0x2D,0x2E,KEY_BACKSPACE},
	{KEY_TAB,KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,0x2F,0x30,0x31},
	{KEY_CAPS_LOCK,KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,KEY_H,KEY_J,KEY_K,KEY_L,0x33,0x34,KEY_RETURN,KEY_NONE},
	{KEY_SHIFT_LEFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KEY_N,KEY_M,0x36,0x37,0x38,KEY_SHIFT_RIGHT,KEY_NONE,KEY_NONE},
	{KEY_CONTROL_LEFT,0x00,KEY_ALT_LEFT,KEY_NONE,KEY_SPACE,GOTOCOMMANDMODE,KEY_DELETE,KEY_APPLICATION,KEY_CONTROL_RIGHT,' ',' ',' ',' ',' '}
};

byte rowPins[ROWS] = {A0, A1, A2, A3, A4}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {A5, A6, A7, A8, A9, A10, A11, 22, 23, 24, 25, 26, 27, 28}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);