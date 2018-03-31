// NotifyBar.h

#ifndef _NOTIFYBAR_h
#define _NOTIFYBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GUIElement.h"
#include "GUIButton.h"
#include "Color.h"

class NotifyBar : public Drawable
{
protected:
	GUIElement * selectedElement;
	int yPos, height;
	Color color;

public:
	NotifyBar();
	void begin(int _yPos, int _height, Color _col);

	virtual void update();
	using Drawable::draw;
	virtual void draw(ILI9341_t3 tft);
};


#endif

