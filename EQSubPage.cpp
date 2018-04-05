// 
// 
// 

#include "EQSubPage.h"

void EQSubPage::begin(int _xPos, int _yPos, int _width, int _height)
{
	GUIPage::begin("EQSub", _xPos, _yPos, _width, _height);
	for (int i = 0; i < buttonsAm; i++) {
		GUIButtons[i].begin(this, xPos + 10, yPos + 10 + 25 * i, width - 20, 20, Color(240, 20, 50, HSB_MODE), "Test", 2);
		if (i == 0) GUIButtons[i].prevElem = NULL;
		else GUIButtons[i].prevElem = &GUIButtons[i - 1];
		if (i == buttonsAm - 1) GUIButtons[i].nextElem = NULL;
		else GUIButtons[i].nextElem = &GUIButtons[i + 1];
	}
}

void EQSubPage::setUpButton(int buttonIdx, String _name, float* _source, void(*_callback)(float, void *))
{
	GUIButtons[buttonIdx].setName(_name);
	GUIButtons[buttonIdx].setSource(_source);
	GUIButtons[buttonIdx].setCallback(_callback, this);
}

void EQSubPage::setTopElem(GUIElement * _elem)
{
	GUIButtons[0].prevElem = _elem;
	_elem->nextElem = &GUIButtons[0];
}

void EQSubPage::update()
{
	for (int i = 0; i < buttonsAm; i++) {
		GUIButtons[i].update();
	}
}

void EQSubPage::draw(ILI9341_t3 tft)
{
	GUIPage::draw(tft);
	for (int i = 0; i < buttonsAm; i++) {
		GUIButtons[i].draw(tft, updateDrawing);
	}
	updateDrawing = false;
}

void EQSubPage::draw(ILI9341_t3 tft, bool forceDraw)
{
	updateDrawing = forceDraw || updateDrawing;
	draw(tft);
}
