// 
// 
// 

#include "EQPage.h"

extern String saveString;

void EQPage::begin(int _xPos, int _yPos, int _width, int _height, String _name, EQ_SETTINGS* _EQSettings)
{
	GUIPage::begin(_name + " EQ", _xPos, _yPos, _width, _height);
	EQSettings = _EQSettings;

	// eq frequency graph,
	int eqGraphHeight = 145;

	filterButton.begin(this, xPos + 10, yPos + eqGraphHeight, width - 20, 25, Color(220, 0, 60, HSB_MODE), "Filter", 2);
	filterButton.setSource(&currentSubPageName);
	filterButton.setCallback(EQPage::switchSubPageCallback, this);

	for (int i = 0; i < subPagesAm; i++) {
		EQSubPages[i].begin(0, filterButton.getYpos() + filterButton.getHeight(), width, height - filterButton.getHeight());
		EQSubPages[i].setTopElem(&filterButton);
	}

	EQSubPages[0].setUpButton(0, "Preset", &currentPresetSlotName, switchPresetSlot, this);
	EQSubPages[0].setUpButton(1, "Load", &saveString, loadPresetSlot, this);
	EQSubPages[0].setUpButton(2, "Save", &saveString, savePresetSlot, this);
	EQSubPages[0].setName("Presets");

	EQSubPages[1].setUpButton(0, "Gain", &EQSettings->lowShelfGain, setLowShelfGain, this);
	EQSubPages[1].setUpButton(1, "Frequency", &EQSettings->lowShelfFreq, setLowShelfFreq, this);
	EQSubPages[1].setUpButton(2, "Q", &EQSettings->lowShelfQ, setLowShelfQ, this);
	EQSubPages[1].setName("Low Shelf");

	EQSubPages[2].setUpButton(0, "Gain", &EQSettings->band1Gain, setBand1Gain, this);
	EQSubPages[2].setUpButton(1, "Frequency", &EQSettings->band1Freq, setBand1Freq, this);
	EQSubPages[2].setUpButton(2, "Q", &EQSettings->band1Q, setBand1Q, this);
	EQSubPages[2].setName("Band 1");

	EQSubPages[3].setUpButton(0, "Gain", &EQSettings->band2Gain, setBand2Gain, this);
	EQSubPages[3].setUpButton(1, "Frequency", &EQSettings->band2Freq, setBand2Freq, this);
	EQSubPages[3].setUpButton(2, "Q", &EQSettings->band2Q, setBand2Q, this);
	EQSubPages[3].setName("Band 2");

	EQSubPages[4].setUpButton(0, "Gain", &EQSettings->highShelfGain, setHighShelfGain, this);
	EQSubPages[4].setUpButton(1, "Frequency", &EQSettings->highShelfFreq, setHighShelfFreq, this);
	EQSubPages[4].setUpButton(2, "Q", &EQSettings->highShelfQ, setHighShelfQ, this);
	EQSubPages[4].setName("High Shelf");

	switchSubPage(0);
}

void EQPage::switchSubPage(int idx) {
	if (idx < 0 || idx >= subPagesAm) return;
	currentSubPageIdx = idx;
	currentSubPage = &EQSubPages[currentSubPageIdx];
	currentSubPageName = currentSubPage->getName();
	currentSubPage->setTopElem(&filterButton);
	currentSubPage->setSelectedElem(NULL);
	currentSubPage->resetDrawing();
}

void EQPage::setTopElem(GUIElement * _elem)
{
	filterButton.prevElem = _elem;
	_elem->nextElem = &filterButton;
}

void EQPage::switchSubPageCallback(float d, void * this_pointer)
{
	EQPage * self = static_cast<EQPage*>(this_pointer);
	if (d > 0)	self->switchSubPage(self->currentSubPageIdx + 1);
	else self->switchSubPage(self->currentSubPageIdx + -1);
}



void EQPage::update()
{
	filterButton.update();
	currentSubPage->update();
}

bool EQPage::inputUp()
{
	if (currentSubPage->inputUp())
		return true;
	return GUIPage::inputUp();
}

bool EQPage::inputDown()
{
	if (currentSubPage->inputDown())
		return true;
	return GUIPage::inputDown();
}

bool EQPage::inputLeft()
{
	if (currentSubPage->inputLeft())
		return true;
	return GUIPage::inputLeft();
}

bool EQPage::inputRight()
{
	if (currentSubPage->inputRight())
		return true;
	return GUIPage::inputRight();
}

void EQPage::draw(ILI9341_t3 tft)
{
	GUIPage::draw(tft);
	filterButton.draw(tft, updateDrawing);
	currentSubPage->draw(tft, updateDrawing);
	updateDrawing = false;
}
