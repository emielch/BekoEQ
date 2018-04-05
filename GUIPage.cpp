// 
// 
// 

#include "GUIPage.h"

GUIPage::GUIPage()
	:name(""), xPos(0), yPos(0)
{
}

void GUIPage::begin(String _name, int _xPos, int _yPos, int _width, int _height) {
	name = _name;
	xPos = _xPos;
	yPos = _yPos;
	width = _width;
	height = _height;
}

void GUIPage::setTopElem(GUIElement * _elem)
{
}

void GUIPage::update() {
}

void GUIPage::draw(ILI9341_t3 tft) {
	if (updateDrawing) tft.fillRect(xPos, yPos, tft.width() - xPos, tft.height() - yPos, ILI9341_BLACK);
}

void GUIPage::setSelectedElem(GUIElement * elem)
{
	selectedElement = elem;
}

void GUIPage::setName(String _name)
{
	name = _name;
}

String GUIPage::getName()
{
	return name;
}

bool GUIPage::inputUp()
{
	if (selectedElement == NULL) return false;
	selectedElement->inputUp();
	return true;
}

bool GUIPage::inputDown()
{
	if (selectedElement == NULL) return false;
	selectedElement->inputDown();
	return true;
}

bool GUIPage::inputLeft()
{
	if (selectedElement == NULL) return false;
	selectedElement->inputLeft();
	return true;
}

bool GUIPage::inputRight()
{
	if (selectedElement == NULL) return false;
	selectedElement->inputRight();
	return true;
}

void GUIPage::buttonPress(int val)
{
}

