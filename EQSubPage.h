// EQSubPage.h

#ifndef _EQSUBPAGE_h
#define _EQSUBPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GUIPage.h"


class EQSubPage : public GUIPage
{
protected:
	const static int buttonsAm = 3;
	GUIButton GUIButtons[buttonsAm];

public:
	EQSubPage() {};
	void begin(int _xPos, int _yPos, int _width, int _height);
	void setUpButton(int buttonIdx, String _name, float * _source, void(*_callback)(float, void *), void* page);
	void setUpButton(int buttonIdx, String _name, String * _source, void(*_callback)(float, void *), void* page);
	void setTopElem(GUIElement* _elem);
	void update();
	void draw(ILI9341_t3 tft);
	void draw(ILI9341_t3 tft, bool forceDraw);
};


#endif

