// GUIElement.h

#ifndef _GUIELEMENT_h
#define _GUIELEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "wprogram.h"
#else
#include "WProgram.h"
#endif

#include "Drawable.h"
#include <font_Arial.h>
#include <font_ArialBold.h>
#include "Color.h"

class GUIPage;

class GUIElement : public Drawable {
protected:
	int xPos, yPos, width, height;
	boolean selected = false;
	GUIPage* onPage;
	Color color;
	Color colorSelect;
	String name;


public:
	GUIElement();
	void begin(GUIPage* _onPage, int _xPos, int _yPos, int _width, int _height, Color _color, Color _colorSel, String _name);

	using Drawable::draw;
	virtual void draw(ILI9341_t3 tft);

	void select();
	void deselect();

	virtual bool inputUp();
	virtual bool inputDown();
	virtual bool inputLeft();
	virtual bool inputRight();

	GUIElement* prevElem;
	GUIElement* nextElem;

	int getWidth();
	int getHeight();
	int getXpos();
	int getYpos();

};

#endif

