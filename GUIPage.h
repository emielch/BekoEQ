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
	
	int xPos, yPos, width, height;
	String name;

public:
	GUIPage();
	void begin(String _name, int _xPos, int _yPos, int _width, int _height);
	virtual void setTopElem(GUIElement* _elem);

	virtual void update();
	using Drawable::draw;
	virtual void draw(ILI9341_t3 tft);
	void setSelectedElem(GUIElement* elem);
	void setName(String _name);
	String getName();

	virtual bool inputUp();
	virtual bool inputDown();
	virtual bool inputLeft();
	virtual bool inputRight();

	virtual void buttonPress(int val);
};


#endif

