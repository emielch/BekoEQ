// SettingsPage.h

#ifndef _SETTINGSPAGE_h
#define _SETTINGSPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GUIPage.h"

class SettingsPage : public GUIPage
{
protected:
	int buttonsAm = 4;
	GUIButton GUIButtons[4];

public:
	SettingsPage() {};
	void begin(int _xPos, int _yPos);
	void setTopElem(GUIElement * _elem);
	void update();
	void draw(ILI9341_t3 tft);
};


#endif

