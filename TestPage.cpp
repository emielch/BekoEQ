// 
// 
// 

#include "TestPage.h"

TestPage::TestPage()
{
	for (int i = 0; i < NUM_ELEM; i++) {
		GUIButtons[i] = GUIButton(this, 10, 10 + 25 * i, 220, 20, Color(240, 20, 50, HSB_MODE), "Test", 2);
		if (i == 0) GUIButtons[i].prevElem = &GUIButtons[NUM_ELEM - 1];
		else GUIButtons[i].prevElem = &GUIButtons[i - 1];
		if (i == NUM_ELEM - 1) GUIButtons[i].nextElem = &GUIButtons[0];
		else GUIButtons[i].nextElem = &GUIButtons[i + 1];
	}


	GUIButtons[0].setCallback(setLowShelfFreq);
	GUIButtons[0].setSource(&lowShelfFreq);
	GUIButtons[0].setName("lowFreq");

	GUIButtons[1].setCallback(setBand1Freq);
	GUIButtons[1].setSource(&band1Freq);
	GUIButtons[1].setName("band1Freq");

	GUIButtons[2].setCallback(setBand2Freq);
	GUIButtons[2].setSource(&band2Freq);
	GUIButtons[2].setName("band2Freq");

	GUIButtons[3].setCallback(setHighShelfFreq);
	GUIButtons[3].setSource(&highShelfFreq);
	GUIButtons[3].setName("highFreq");

	GUIButtons[4].setCallback(setLowShelfGain);
	GUIButtons[4].setSource(&lowShelfGain);
	GUIButtons[4].setName("lowGain");

	GUIButtons[5].setCallback(setBand1Gain);
	GUIButtons[5].setSource(&band1Gain);
	GUIButtons[5].setName("band1Gain");

	GUIButtons[6].setCallback(setBand2Gain);
	GUIButtons[6].setSource(&band2Gain);
	GUIButtons[6].setName("band2Gain");

	GUIButtons[7].setCallback(setHighShelfGain);
	GUIButtons[7].setSource(&highShelfGain);
	GUIButtons[7].setName("highGain");

	GUIButtons[8].setCallback(setLowShelfQ);
	GUIButtons[8].setSource(&lowShelfQ);
	GUIButtons[8].setName("lowQ");

	GUIButtons[9].setCallback(setBand1Q);
	GUIButtons[9].setSource(&band1Q);
	GUIButtons[9].setName("band1Q");

	GUIButtons[10].setCallback(setBand2Q);
	GUIButtons[10].setSource(&band2Q);
	GUIButtons[10].setName("band2Q");

	GUIButtons[11].setCallback(setHighShelfQ);
	GUIButtons[11].setSource(&highShelfQ);
	GUIButtons[11].setName("highQ");

	selectedElement = &GUIButtons[0];
	selectedElement->select();
}

void TestPage::update() {
	for (int i = 0; i < NUM_ELEM; i++) {
		GUIButtons[i].update();
	}
}

void TestPage::draw(ILI9341_t3 tft) {
	for (int i = 0; i < NUM_ELEM; i++) {
		GUIButtons[i].draw(tft, updateDrawing);
	}
	updateDrawing = false;
}