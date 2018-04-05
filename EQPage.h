// EQPage.h

#ifndef _EQPAGE_h
#define _EQPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

#include "GUIPage.h"
#include "EQSubPage.h"

extern float lowShelfFreq;
extern float band1Freq;
extern float band2Freq;
extern float highShelfFreq;

extern float lowShelfGain;
extern float band1Gain;
extern float band2Gain;
extern float highShelfGain;

extern float lowShelfQ;
extern float band1Q;
extern float band2Q;
extern float highShelfQ;

extern void setLowShelfFreq(float freq, void* page);
extern void setBand1Freq(float freq, void* page);
extern void setBand2Freq(float freq, void* page);
extern void setHighShelfFreq(float freq, void* page);

extern void setLowShelfGain(float gain, void* page);
extern void setBand1Gain(float gain, void* page);
extern void setBand2Gain(float gain, void* page);
extern void setHighShelfGain(float gain, void* page);

extern void setLowShelfQ(float q, void* page);
extern void setBand1Q(float q, void* page);
extern void setBand2Q(float q, void* page);
extern void setHighShelfQ(float q, void* page);


class EQPage : public GUIPage
{
protected:
	GUIButton filterButton;
	const static int subPagesAm = 4;
	EQSubPage EQSubPages[subPagesAm];
	EQSubPage* currentSubPage;
	int currentSubPageIdx;

public:
	EQPage() {};
	String currentSubPageName;
	void begin(int _xPos, int _yPos, int _width, int _height);
	void switchSubPage(int idx);
	void setTopElem(GUIElement* _elem);
	static void switchSubPageCallback(float d, void * this_pointer);
	void update();
	bool inputUp();
	bool inputDown();
	bool inputLeft();
	bool inputRight();
	void draw(ILI9341_t3 tft);
};

#endif
