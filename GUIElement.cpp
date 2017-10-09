// 
// 
// 

#include "GUIElement.h"
#include "GUIPage.h"


GUIElement::GUIElement()
{
}

GUIElement::GUIElement(GUIPage* _onPage, int _xPos, int _yPos, int _width, int _height, Color _color)
	: onPage(_onPage), xPos(_xPos), yPos(_yPos), width( _width), height(_height), color(_color){

}

void GUIElement::draw(ILI9341_t3 tft){
	if (!updateDrawing) return;

	Color col = color;
	if (selected) col.setHSB(col.hue(),100,100);

	int bgColor = col.getInt();

	tft.fillRoundRect(xPos, yPos, width, height, 4, bgColor);

	updateDrawing = false;
}

void GUIElement::select()
{
	selected = true;
	updateDrawing = true;
}

void GUIElement::deselect()
{
	selected = false;
	updateDrawing = true;
}

void GUIElement::inputUp()
{
	if (prevElem == NULL) return;
	deselect();
	prevElem->select();
	onPage->selectElem(prevElem);
}

void GUIElement::inputDown()
{
	if (nextElem == NULL) return;
	deselect();
	nextElem->select();
	onPage->selectElem(nextElem);
}

void GUIElement::inputLeft()
{
}

void GUIElement::inputRight()
{
}

int GUIElement::getWidth(){
	return width;
}

int GUIElement::getHeight(){
	return height;
}

int GUIElement::getXpos(){
	return xPos;
}

int GUIElement::getYpos(){
	return yPos;
}
