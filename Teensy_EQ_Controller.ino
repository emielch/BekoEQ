/*
 Name:		Teensy_EQ_Controller.ino
 Created:	10/5/2017 10:48:42 PM
 Author:	emiel
*/


#include "EQSubPage.h"
#include "EQPage.h"
#include "AudioLevelBar.h"
#include "SettingsPage.h"
#include "NotifyBar.h"
#include "NavBar.h"
#include "GUIButton.h"
#include "Drawable.h"
#include "GUIPage.h"
#include "GUI.h"
#include "GUIElement.h"

#include <Bounce.h>

#define SPEAKER_ENABLE 6
#define BUTTON_1 8
#define BUTTON_2 17
#define BAT_SENSE 15

Bounce button1 = Bounce(BUTTON_1, 10);  // 10 ms debounce
Bounce button2 = Bounce(BUTTON_2, 10);  // 10 ms debounce


GUI gui;
elapsedMillis sinceNext;
unsigned long previousMicros = 0;

void setup() {
	setupAudio();
	analogReadRes(12);
	pinMode(SPEAKER_ENABLE, OUTPUT);
	pinMode(BAT_SENSE, INPUT);
	pinMode(BUTTON_1, INPUT);
	pinMode(BUTTON_2, INPUT);
	setSpeaker(1,NULL);
}


void loop() {
	long newMicros = micros();
	uint_fast16_t elapsed = newMicros - previousMicros;
	previousMicros = newMicros;
	float dt = elapsed * (100.0f / 1000000);  // 1.0==exactly 100fps. 4.0==25fps, 4x slower

	updateEncoders();
	updateButtons();
	updateAudio(dt);
	updateBatVolt();

	gui.update(dt);
	gui.draw();
}

