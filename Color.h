#ifndef Color_h
#define Color_h

#include "Arduino.h"

#define RGB_MODE 0
#define HSB_MODE 1

// ---- color stuff ----

struct RGB {
  byte r;  // 255
  byte g;  // 255
  byte b;  // 255
};

struct HSB {
  int h;  // 360
  byte s;  // 100
  byte b;  // 100
};

class Color {
	public:
		Color();
		Color(int v1, byte v2, byte v3, byte mode);
		
		void setRGB(byte r, byte g, byte b);
		void setHSB(unsigned int h, byte s, byte b);
		
		byte red();
		byte green();
		byte blue();
		int hue();
		byte saturation();
		byte brightness();

		int getInt();
		
		void add(Color toAdd, float fadeFac);
		void add(Color toAdd);
		void addHDR(Color toAdd, float fadeFac);
		void multiply(Color toMult, float fadeFac);
		void multiply(Color toMult);
		void multiply(float multFac);
		void fade(Color toFade, float fadeFac);
		void fade(Color c1, Color c2, float fadeFac);
	
	private:
		RGB RGB_color;
		HSB HSB_color;
		boolean RGB_updated;
		boolean HSB_updated;
		
		HSB RGBtoHSB(RGB *color);
		RGB HSBtoRGB(HSB *color);
		
		void updateHSB();
		void updateRGB();
};

#endif