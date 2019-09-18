// 
// 
// 

#include "GUIElement.h"
#include "GUIPage.h"


GUIElement::GUIElement()
{
}

void GUIElement::begin(GUIPage* _onPage, int _xPos, int _yPos, int _width, int _height, Color _color, Color _colorSel, String _name) {
	onPage = _onPage;
	xPos = _xPos;
	yPos = _yPos;
	width = _width;
	height = _height;
	color = _color;
	colorSelect = _colorSel;
	name = _name;
}

void GUIElement::draw(ILI9341_t3 tft) {
	if (!updateDrawing) return;

	int bgColor;
	if (selected) bgColor = colorSelect.getInt();
	else bgColor = color.getInt();

	tft.fillRoundRect(xPos, yPos, width, height, 4, bgColor);

	updateDrawing = false;
}

void GUIElement::select()
{
	selected = true;
	updateDrawing = true;
	onPage->setSelectedElem(this);
}

void GUIElement::deselect()
{
	selected = false;
	updateDrawing = true;
	onPage->setSelectedElem(NULL);
}

bool GUIElement::inputUp()
{
	if (prevElem == NULL) return false;
	deselect();
	prevElem->select();
	return true;
}

bool GUIElement::inputDown()
{
	if (nextElem == NULL) return false;
	deselect();
	nextElem->select();
	return true;
}

bool GUIElement::inputLeft()
{
	return false;
}

bool GUIElement::inputRight()
{
	return false;
}

int GUIElement::getWidth() {
	return width;
}

int GUIElement::getHeight() {
	return height;
}

int GUIElement::getXpos() {
	return xPos;
}

int GUIElement::getYpos() {
	return yPos;
}
