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
	Color colSel = Color(_color.hue(), 100, 100, HSB_MODE);
	GUIElement::begin((GUIPage*)_gui, _xPos, _yPos, _width, _height, _color, colSel, "NavBar");
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
	char copy[50];
	printText.toCharArray(copy, 50);
	tft.setFont(Arial_20_Bold);
	int textPixelLen = tft.strPixelLen(copy);
	tft.setCursor((xPos + width/2) - textPixelLen/2, (yPos + height/2) - 12);

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