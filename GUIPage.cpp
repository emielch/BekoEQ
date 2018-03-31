// 
// 
// 

#include "GUIPage.h"

GUIPage::GUIPage()
	:name(""), xPos(0), yPos(0)
{
}

void GUIPage::begin(String _name, int _xPos, int _yPos) {
	name = _name;
	xPos = _xPos;
	yPos = _yPos;
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

void GUIPage::inputUp()
{
	if (selectedElement == NULL) return;
	selectedElement->inputUp();
}

void GUIPage::inputDown()
{
	if (selectedElement == NULL) return;
	selectedElement->inputDown();
}

void GUIPage::inputLeft()
{
	if (selectedElement == NULL) return;
	selectedElement->inputLeft();
}

void GUIPage::inputRight()
{
	if (selectedElement == NULL) return;
	selectedElement->inputRight();
}

void GUIPage::buttonPress(int val)
{
}

