// 
// 
// 

#include "SettingsPage.h"

void SettingsPage::begin(int _xPos, int _yPos, int _width, int _height) {

	GUIPage::begin("Settings", _xPos, _yPos, _width, _height);
	for (int i = 0; i < buttonsAm; i++) {
		GUIButtons[i].begin(this, xPos + 10, yPos + 10 + 25 * i, 220, 20, Color(240, 20, 50, HSB_MODE), "Test", 2);
		if (i == 0) GUIButtons[i].prevElem = NULL;
		else GUIButtons[i].prevElem = &GUIButtons[i - 1];
		if (i == buttonsAm - 1) GUIButtons[i].nextElem = NULL;
		else GUIButtons[i].nextElem = &GUIButtons[i + 1];
	}


	GUIButtons[0].setCallback(moveScreenBri, this);
	GUIButtons[0].setSource(&labelScreenBri);
	GUIButtons[0].setName("Brightness");

	GUIButtons[1].setCallback(moveJackIn, this);
	GUIButtons[1].setSource(&labelJackIn);
	GUIButtons[1].setName("Jack In");

	GUIButtons[2].setCallback(moveUSBIn, this);
	GUIButtons[2].setSource(&labelUSBIn);
	GUIButtons[2].setName("USB In");

	GUIButtons[3].setCallback(moveSpeakerOut, this);
	GUIButtons[3].setSource(&labelSpeaker);
	GUIButtons[3].setName("Speaker");
}

void SettingsPage::setTopElem(GUIElement* _elem) {
	GUIButtons[0].prevElem = _elem;
	_elem->nextElem = &GUIButtons[0];
}

void SettingsPage::update() {
	for (int i = 0; i < buttonsAm; i++) {
		GUIButtons[i].update();
	}
}

void SettingsPage::draw(ILI9341_t3 tft) {
	GUIPage::draw(tft);
	for (int i = 0; i < buttonsAm; i++) {
		GUIButtons[i].draw(tft, updateDrawing);
	}
	updateDrawing = false;
}