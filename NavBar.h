// NavBar.h

#ifndef _NAVBAR_h
#define _NAVBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GUIElement.h"
#include "GUIButton.h"
#include "Color.h"

class GUI;

class NavBar : public GUIElement
{
protected:
	GUI * gui;
	int pageAm;
	GUIPage** pages;
	int currentPageID = 0;

public:
	NavBar();
	void begin(GUI* _gui, int _xPos, int _yPos, int _width, int _height, Color _color);
	void setPages(GUIPage** _pages, int _pageAm);

	void update();
	void draw(ILI9341_t3 tft);

	void inputLeft();
	void inputRight();
};



#endif

