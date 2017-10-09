/*
 Name:		Teensy_EQ_Controller.ino
 Created:	10/5/2017 10:48:42 PM
 Author:	emiel
*/

// the setup function runs once when you press reset or power the board

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

// the loop function runs over and over again until power down or reset
void loop() {
	updateEncoders();

	gui.update();
	gui.draw();
}