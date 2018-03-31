// GUIPage.h

#ifndef _GUIPAGE_h
#define _GUIPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "wprogram.h"
#else
#include "WProgram.h"
#endif

#include "GUIElement.h"
#include "GUIButton.h"
#include "NavBar.h"


class GUIPage : public Drawable
{
protected:
	GUIElement* selectedElement;
	
	int xPos, yPos;

public:
	GUIPage();
	String name;
	void begin(String _name, int _xPos, int _yPos);
	virtual void setTopElem(GUIElement* _elem);

	virtual void update();
	using Drawable::draw;
	virtual void draw(ILI9341_t3 tft);
	void setSelectedElem(GUIElement* elem);

	void inputUp();
	void inputDown();
	void inputLeft();
	void inputRight();

	virtual void buttonPress(int val);
};


#endif

