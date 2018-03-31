// GUI.h

#ifndef _GUI_h
#define _GUI_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "wprogram.h"
#else
#include "WProgram.h"
#endif

#include "SPI.h"
#include "ILI9341_t3.h"
#include "NavBar.h"
#include "NotifyBar.h"
#include "GUIPage.h"
#include "TestPage.h"
#include "SettingsPage.h"

// For the Adafruit shield, these are the default.
#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
#define BACKLIGHT   3



class GUI : public GUIPage
{
protected:
	ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);
	GUIPage* currentPage;
	NavBar navBar;
	NotifyBar notifyBar;
	unsigned int lastInput = 0;
	unsigned int lastTimeoutInput = 0;
	bool screenOn;
	float backlightPower = 0;
	byte screenBri = 20;
	int topBarHeight;

	TestPage testPage;
	SettingsPage settingsPage;

	static const int pageAm = 2;
	GUIPage* pages[pageAm];

public:
	GUI();
	void screenSwitch(bool on);
	void setScreenBri(int bri);
	void update();
	void draw();
	bool inputBlock();

	void inputUp(int val);
	void inputDown(int val);
	void inputLeft(int val);
	void inputRight(int val);
	void switchPage(GUIPage * page);
};

#endif

