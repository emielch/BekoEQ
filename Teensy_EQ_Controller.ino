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
#include <Adafruit_NeoPixel.h>

#define SPEAKER_ENABLE 6
#define BUTTON_1 8
#define BUTTON_2 17
#define BAT_SENSE 15
#define NEOPIXEL_PIN 16

Bounce button1 = Bounce(BUTTON_1, 10);  // 10 ms debounce
Bounce button2 = Bounce(BUTTON_2, 10);  // 10 ms debounce

Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


GUI gui;
elapsedMillis sinceNext;
unsigned long previousMicros = 0;

byte screenBri = 20;
byte jackSetting = 0;
byte usbSetting = 0;
byte speakerSetting = 1;


void setup() {
	setupAudio();
	analogReadRes(12);
	pinMode(SPEAKER_ENABLE, OUTPUT);
	pinMode(BAT_SENSE, INPUT);
	pinMode(BUTTON_1, INPUT);
	pinMode(BUTTON_2, INPUT);
	loadSettings();
	loadEQSettings(0,0);
	loadEQSettings(1,1);
	goToPresetSlot(0);

	strip.begin();
	strip.show();
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
	updateSaving();

	gui.update(dt);
	gui.draw();
}

