// GUIButton.h

#ifndef _GUIBUTTON_h
#define _GUIBUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

#include "GUIElement.h"

class GUIButton : public GUIElement
{
 protected:
	 bool updateVal = true;
	 int tSize;
	 int* intSource = NULL;
	 float* floatSource = NULL;
	 String* stringSource = NULL;
	 void(*callback)(float);
	 unsigned long lastInput = 0;
	 void drawVal(ILI9341_t3 tft);
	 

 public:
	 
	 GUIButton();
	 void begin(GUIPage* _onPage, int _xPos, int _yPos, int _width, int _height, Color _color, String _name, int _tSize);
	 void setName(String _name);
	 void setCallback(void(*_callback)(float));
	 void setSource(float* _source);
	 void setSource(int* _source);
	 void setSource(String* _source);

	 using GUIElement::draw;
	 void draw(ILI9341_t3 tft);

	 void inputLeft();
	 void inputRight();

	 float accel();
	
};

#endif

