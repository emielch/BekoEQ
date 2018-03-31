/*
 Name:		Teensy_EQ_Controller.ino
 Created:	10/5/2017 10:48:42 PM
 Author:	emiel
*/


#include "SettingsPage.h"
#include "NotifyBar.h"
#include "NavBar.h"
#include "GUIButton.h"
#include "Drawable.h"
#include "TestPage.h"
#include "GUIPage.h"
#include "GUI.h"
#include "GUIElement.h"

GUI gui;
elapsedMillis sinceNext;

void setup() {
	setupAudio();
}


void loop() {
	updateEncoders();
	updateAudio();

	gui.update();
	gui.draw();
}

int screenBri = 20;
void setScreenBri(float b) {
	screenBri += b;
	if (screenBri < 5) screenBri = 5;
	else if (screenBri > 255) screenBri = 255;
	gui.setScreenBri(screenBri);
}