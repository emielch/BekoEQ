// 
// 
// 

#include "GUIPage.h"

GUIPage::GUIPage()
{
}

void GUIPage::update() {
}

void GUIPage::draw(ILI9341_t3 tft) {
}

void GUIPage::selectElem(GUIElement * elem)
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

