// TestPage.h

#ifndef _TESTPAGE_h
#define _TESTPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "wprogram.h"
#else
#include "WProgram.h"
#endif


#include "GUIPage.h"


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

extern void setLowShelfFreq(float freq);
extern void setBand1Freq(float freq);
extern void setBand2Freq(float freq);
extern void setHighShelfFreq(float freq);

extern void setLowShelfGain(float gain);
extern void setBand1Gain(float gain);
extern void setBand2Gain(float gain);
extern void setHighShelfGain(float gain);

extern void setLowShelfQ(float q);
extern void setBand1Q(float q);
extern void setBand2Q(float q);
extern void setHighShelfQ(float q);

class TestPage : public GUIPage
{
protected:
	const static int buttonsAm = 12;
	GUIButton GUIButtons[buttonsAm];

public:
	TestPage() {};
	void begin(int _xPos, int _yPos);
	void setTopElem(GUIElement* _elem);
	void update();
	void draw(ILI9341_t3 tft);
};

#endif

