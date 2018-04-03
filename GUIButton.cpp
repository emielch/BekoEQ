// 
// 
// 

#include "GUIButton.h"

GUIButton::GUIButton()
{
}

void GUIButton::begin(GUIPage* _onPage, int _xPos, int _yPos, int _width, int _height, Color _color, String _name, int _tSize) {
	Color colUnsel = Color(_color.hue(), _color.saturation(), 40, HSB_MODE);
	GUIElement::begin(_onPage, _xPos, _yPos, _width, _height, colUnsel, _color, _name);
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

void GUIButton::setSource(String * _source)
{
	stringSource = _source;
}

void GUIButton::draw(ILI9341_t3 tft)
{
	if (updateDrawing) {
		GUIElement::draw(tft);
		tft.setFont(Arial_14);
		tft.setTextSize(tSize);
		tft.setCursor(xPos + 4, (yPos + height / 2) - 4 * tSize);
		tft.println(name);
		drawVal(tft);
		updateDrawing = false;
	}
	if (updateVal) {
		drawVal(tft);
	}
}

void GUIButton::drawVal(ILI9341_t3 tft) {
	Color col = color;
	if (selected) col.setHSB(col.hue(), col.saturation() + 10, col.brightness());
	else col.setHSB(col.hue(), col.saturation(), col.brightness() - 20);
	int bgColor = col.getInt();
	tft.fillRoundRect(xPos + width / 2, yPos, width / 2, height, 4, bgColor);

	String printText = "";
	if (intSource != NULL) printText += String(*intSource);
	if (floatSource != NULL) printText += String(*floatSource);
	if (stringSource != NULL) printText += *stringSource;

	tft.setFont(Arial_14);
	tft.setTextSize(tSize);
	tft.setCursor((xPos + width * 0.75) - printText.length() * 3 * tSize, (yPos + height / 2) - 4 * tSize);
	tft.println(printText);
	updateVal = false;
}

void GUIButton::inputLeft()
{
	if (callback == NULL) return;
	callback(-1 * accel());
	updateVal = true;
}

void GUIButton::inputRight()
{
	if (callback == NULL) return;
	callback(1 * accel());
	updateVal = true;
}

float GUIButton::accel()
{
	unsigned long inputTime = millis();
	unsigned long inputInterval = inputTime - lastInput;
	lastInput = inputTime;

	return 200. / inputInterval;
}
