// 
// 
// 

#include "EQPage.h"

void EQPage::begin(int _xPos, int _yPos, int _width, int _height)
{
	GUIPage::begin("EQ", _xPos, _yPos, _width, _height);

	// eq frequency graph,
	int eqGraphHeight = 145;

	filterButton.begin(this, xPos + 10, yPos + eqGraphHeight, width - 20, 25, Color(220, 0, 60, HSB_MODE), "Filter", 2);
	filterButton.setSource(&currentSubPageName);
	filterButton.setCallback(EQPage::switchSubPageCallback, this);

	for (int i = 0; i < subPagesAm; i++) {
		EQSubPages[i].begin(0, filterButton.getYpos() + filterButton.getHeight(), width, height - filterButton.getHeight());
		EQSubPages[i].setTopElem(&filterButton);
	}

	EQSubPages[0].setUpButton(0, "Preset", &currentPresetSlotName, switchPresetSlot);
	EQSubPages[0].setUpButton(1, "Load", &current_EQ_settings.lowShelfFreq, loadPresetSlot);
	EQSubPages[0].setUpButton(2, "Save", &current_EQ_settings.lowShelfFreq, savePresetSlot);
	EQSubPages[0].setName("Presets");

	EQSubPages[1].setUpButton(0, "Gain", &current_EQ_settings.lowShelfGain, setLowShelfGain);
	EQSubPages[1].setUpButton(1, "Frequency", &current_EQ_settings.lowShelfFreq, setLowShelfFreq);
	EQSubPages[1].setUpButton(2, "Q", &current_EQ_settings.lowShelfQ, setLowShelfQ);
	EQSubPages[1].setName("Low Shelf");

	EQSubPages[2].setUpButton(0, "Gain", &current_EQ_settings.band1Gain, setBand1Gain);
	EQSubPages[2].setUpButton(1, "Frequency", &current_EQ_settings.band1Freq, setBand1Freq);
	EQSubPages[2].setUpButton(2, "Q", &current_EQ_settings.band1Q, setBand1Q);
	EQSubPages[2].setName("Band 1");

	EQSubPages[3].setUpButton(0, "Gain", &current_EQ_settings.band2Gain, setBand2Gain);
	EQSubPages[3].setUpButton(1, "Frequency", &current_EQ_settings.band2Freq, setBand2Freq);
	EQSubPages[3].setUpButton(2, "Q", &current_EQ_settings.band2Q, setBand2Q);
	EQSubPages[3].setName("Band 2");

	EQSubPages[4].setUpButton(0, "Gain", &current_EQ_settings.highShelfGain, setHighShelfGain);
	EQSubPages[4].setUpButton(1, "Frequency", &current_EQ_settings.highShelfFreq, setHighShelfFreq);
	EQSubPages[4].setUpButton(2, "Q", &current_EQ_settings.highShelfQ, setHighShelfQ);
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
