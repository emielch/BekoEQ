// Drawable.h

#ifndef _DRAWABLE_h
#define _DRAWABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

#include "ILI9341_t3.h"

class Drawable
{
 protected:
	 boolean updateDrawing = true;

 public:
	 Drawable();
	 virtual void update();
	 void resetDrawing();
	 void draw(ILI9341_t3 tft, boolean force);
	 virtual void draw(ILI9341_t3 tft);
};


#endif

