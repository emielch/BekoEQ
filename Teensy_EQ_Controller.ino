/*
 Name:		Teensy_EQ_Controller.ino
 Created:	10/5/2017 10:48:42 PM
 Author:	emiel
*/


#include "AudioLevelBar.h"
#include "SettingsPage.h"
#include "NotifyBar.h"
#include "NavBar.h"
#include "GUIButton.h"
#include "Drawable.h"
#include "TestPage.h"
#include "GUIPage.h"
#include "GUI.h"
#include "GUIElement.h"

#define SPEAKER_ENABLE 6
#define BUTTON_1 8
#define BUTTON_2 17
#define BAT_SENSE 15

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
	attachInterrupt(BUTTON_1, button1isr, RISING);
	attachInterrupt(BUTTON_2, button2isr, RISING);
	setSpeaker(1);
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

