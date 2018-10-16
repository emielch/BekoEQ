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

void GUIButton::setCallback(void(*_callback)(float, void *), void * _page)
{
	callback = _callback;
	callback_page = _page;
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

	char copy[50];
	printText.toCharArray(copy, 50);
	if(selected) tft.setFont(Arial_14_Bold);
	else tft.setFont(Arial_14);
	int textPixelLen = tft.strPixelLen(copy);
	tft.setCursor((xPos + width * 0.75) - textPixelLen / 2, (yPos + height / 2) - 8);

	tft.println(printText);
	updateVal = false;
}

bool GUIButton::inputLeft()
{
	if (callback == NULL) return false;
	callback(-1 * accel(), callback_page);
	updateVal = true;
	return true;
}

bool GUIButton::inputRight()
{
	if (callback == NULL) return false;
	callback(1 * accel(),callback_page);
	updateVal = true;
	return true;
}

float GUIButton::accel()
{
	unsigned long inputTime = millis();
	unsigned long inputInterval = inputTime - lastInput;
	lastInput = inputTime;
	int val = 400. / inputInterval;
	if (val == 0) val = 1;

	return val*0.5;
}
