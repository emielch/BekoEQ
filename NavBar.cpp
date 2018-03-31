// 
// 
// 

#include "NavBar.h"
#include "GUI.h"

NavBar::NavBar()
{
}

void NavBar::begin(GUI* _gui, int _xPos, int _yPos, int _width, int _height, Color _color)
{
	GUIElement::begin((GUIPage*)_gui, _xPos, _yPos, _width, _height, _color, "NavBar");
	gui = _gui;
}

void NavBar::setPages(GUIPage ** _pages, int _pageAm)
{
	pages = _pages;
	pageAm = _pageAm;
}

void NavBar::update()
{
}

void NavBar::draw(ILI9341_t3 tft)
{
	if (!updateDrawing) return;
	GUIElement::draw(tft);


	String printText = pages[currentPageID]->name;
	int textSize = 3;
	tft.setTextSize(textSize);
	tft.setCursor((xPos + width/2) - printText.length() * 3 * textSize, (yPos + height/2) - 4 * textSize);
	//tft.setCursor(xPos+width - printText.length() * 6 * textSize, yPos+height - 8 * textSize);	

	tft.println(printText);

	updateDrawing = false;
}

void NavBar::inputLeft()
{
	if (currentPageID == pageAm - 1) return;
	currentPageID++;
	gui->switchPage(pages[currentPageID]);
	updateDrawing = true;
}

void NavBar::inputRight()
{
	if (currentPageID == 0) return;
	currentPageID--;
	gui->switchPage(pages[currentPageID]);
	updateDrawing = true;
}