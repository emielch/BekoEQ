// 
// 
// 

#include "GUIButton.h"

GUIButton::GUIButton()
{
}

void GUIButton::begin(GUIPage* _onPage, int _xPos, int _yPos, int _width, int _height, Color _color, String _name, int _tSize) {
	GUIElement::begin(_onPage, _xPos, _yPos, _width, _height, _color, _name);
	tSize = _tSize;

}

void GUIButton::setName(String _name)
{
	name = _name;
}

void GUIButton::setCallback(void(*_callback)(float))
{
	callback = _callback;
}

void GUIButton::setSource(float* _source)
{
	floatSource = _source;
}

void GUIButton::setSource(int* _source)
{
	intSource = _source;
}

void GUIButton::draw(ILI9341_t3 tft)
{
	if (!updateDrawing) return;

	GUIElement::draw(tft);

	int PADDING = 2;

	tft.setCursor(xPos + PADDING, yPos + PADDING);
	tft.setTextSize(tSize);

	String printText = name;
	if (intSource != NULL) printText += " " + String(*intSource);
	if (floatSource != NULL) printText += " " + String(*floatSource);

	tft.println(printText);

	updateDrawing = false;
}

void GUIButton::inputLeft()
{
	if (callback == NULL) return;
	callback(-1 * accel());
	updateDrawing = true;
}

void GUIButton::inputRight()
{
	if (callback == NULL) return;
	callback(1 * accel());
	updateDrawing = true;
}

float GUIButton::accel()
{
	unsigned long inputTime = millis();
	unsigned long inputInterval = inputTime - lastInput;
	lastInput = inputTime;

	return 200. / inputInterval;
}
