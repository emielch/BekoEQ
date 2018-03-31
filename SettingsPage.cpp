// 
// 
// 

#include "SettingsPage.h"

void SettingsPage::begin(int _xPos, int _yPos) {

	GUIPage::begin("Settings", _xPos, _yPos);
	for (int i = 0; i < buttonsAm; i++) {
		GUIButtons[i].begin(this, xPos + 10, yPos + 10 + 25 * i, 220, 20, Color(240, 20, 50, HSB_MODE), "Test", 2);
		if (i == 0) GUIButtons[i].prevElem = NULL;
		else GUIButtons[i].prevElem = &GUIButtons[i - 1];
		if (i == buttonsAm - 1) GUIButtons[i].nextElem = NULL;
		else GUIButtons[i].nextElem = &GUIButtons[i + 1];
	}


	//GUIButtons[0].setCallback(setLowShelfFreq);
	//GUIButtons[0].setSource(&lowShelfFreq);
	//GUIButtons[0].setName("lowFreq");

	//GUIButtons[1].setCallback(setBand1Freq);
	//GUIButtons[1].setSource(&band1Freq);
	//GUIButtons[1].setName("band1Freq");

	//GUIButtons[2].setCallback(setBand2Freq);
	//GUIButtons[2].setSource(&band2Freq);
	//GUIButtons[2].setName("band2Freq");

	//GUIButtons[3].setCallback(setHighShelfFreq);
	//GUIButtons[3].setSource(&highShelfFreq);
	//GUIButtons[3].setName("highFreq");
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