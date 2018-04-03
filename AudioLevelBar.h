// AudioLevelBar.h

#ifndef _AUDIOLEVELBAR_h
#define _AUDIOLEVELBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GUIElement.h"
#include "Color.h"
#include <math.h>  

class AudioLevelBar : public Drawable
{
protected:
	GUIElement * selectedElement;
	int xPos, yPos, width, height;
	float* floatSource = NULL;
	float meterVal = 0;
	float prevMeterVal = 0;
	Color bgColor;

public:
	AudioLevelBar();
	void begin(int _xPos, int _yPos, int _width, int _height, Color _bgColor);
	void setSource(float* _source);

	int getHeight();

	void update(float dt);
	void draw(ILI9341_t3 tft);
};


#endif