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

extern bool jackInOn;
extern bool USBInOn;
extern bool speakerOn;
extern float batVolt;

class NotifyBar : public Drawable
{
protected:
	GUIElement * selectedElement;
	bool updateBatVoltTxt = true;
	int batVoltRound = 0;
	int yPos, height;
	Color color;

	bool _jackInOn, _USBInOn, _speakerOn, _batteryOn;

public:
	NotifyBar();
	void begin(int _yPos, int _height, Color _col);

	int getHeight();

	void update();
	void draw(ILI9341_t3 tft);
};


#endif

