// SettingsPage.h

#ifndef _SETTINGSPAGE_h
#define _SETTINGSPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GUIPage.h"

extern void moveScreenBri(float b, void* page);
extern String labelScreenBri;

extern void moveJackIn(float b, void* page);
extern String labelJackIn;

extern void moveUSBIn(float b, void* page);
extern String labelUSBIn;

extern void moveSpeakerOut(float b, void* page);
extern String labelSpeaker;


class SettingsPage : public GUIPage
{
protected:
	int buttonsAm = 4;
	GUIButton GUIButtons[4];

public:
	SettingsPage() {};
	void begin(int _xPos, int _yPos, int _width, int _height);
	void setTopElem(GUIElement * _elem);
	void update();
	void draw(ILI9341_t3 tft);
};


#endif

