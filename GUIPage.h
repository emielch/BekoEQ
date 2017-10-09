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


class GUIPage : public Drawable
{
protected:
	GUIElement* selectedElement;

public:
	GUIPage();

	virtual void update();
	using Drawable::draw;
	virtual void draw(ILI9341_t3 tft);
	void selectElem(GUIElement* elem);

	void inputUp();
	void inputDown();
	void inputLeft();
	void inputRight();

	virtual void buttonPress(int val);
};


#endif

