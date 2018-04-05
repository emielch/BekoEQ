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


	String printText = pages[currentPageIndex]->getName();
	char copy[50];
	printText.toCharArray(copy, 50);
	tft.setFont(Arial_20_Bold);
	int textPixelLen = tft.strPixelLen(copy);
	tft.setCursor((xPos + width/2) - textPixelLen/2, (yPos + height/2) - 12);

	tft.println(printText);

	updateDrawing = false;
}

bool NavBar::inputLeft()
{
	if (currentPageIndex == 0) return false;
	goToPageIndex(currentPageIndex - 1);
	return true;
}

bool NavBar::inputRight()
{
	if (currentPageIndex == pageAm - 1) return false;
	goToPageIndex(currentPageIndex +1);
	return true;
}

void NavBar::goToPageIndex(int idx) {
	currentPageIndex = idx;
	gui->switchPage(pages[currentPageIndex]);
	updateDrawing = true;
}