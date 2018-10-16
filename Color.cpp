
#include "Arduino.h"
#include "Color.h"


Color::Color(){
	RGB_updated = false;
	HSB_updated = false;
}

Color::Color(int v1, byte v2, byte v3, byte mode){
	if(mode == HSB_MODE){
		setHSB(v1, v2, v3);
		return;
	}
	setRGB(v1, v2, v3);
}

void Color::setRGB(byte r, byte g, byte b){
	RGB_color.r = r;
	RGB_color.g = g;
	RGB_color.b = b;
	RGB_updated = true;
	HSB_updated = false;
}

void Color::setHSB(unsigned int h, byte s, byte b){
	HSB_color.h = (h+720)%360;
	HSB_color.s = s;
	HSB_color.b = b;
	RGB_updated = false;
	HSB_updated = true;
}

void Color::updateRGB(){
	RGB_color = HSBtoRGB(&HSB_color);
	RGB_updated = true;
}

void Color::updateHSB(){
	HSB_color = RGBtoHSB(&RGB_color);
	HSB_updated = true;
}

byte Color::red(){
	if(!RGB_updated){
		updateRGB();
	}
	return RGB_color.r;
}

byte Color::green(){
	if(!RGB_updated){
		updateRGB();
	}
	return RGB_color.g;
}

byte Color::blue(){
	if(!RGB_updated){
		updateRGB();
	}
	return RGB_color.b;
}

int Color::hue(){
	if(!HSB_updated){
		updateHSB();
	}
	return HSB_color.h;
}

byte Color::saturation(){
	if(!HSB_updated){
		updateHSB();
	}
	return HSB_color.s;
}

byte Color::brightness(){
	if(!HSB_updated){
		updateHSB();
	}
	return HSB_color.b;
}

int Color::getInt(){
	byte r = red() / 8;
	byte g = green() / 4;
	byte b = blue() / 8;
	return ((int)r << 11) | ((int)g << 5) | b;
}

void Color::add(Color toAdd, float fadeFac){
	if(fadeFac!=0.){
		byte r = constrain(red() + toAdd.red()*fadeFac, 0,255);
		byte g = constrain(green() + toAdd.green()*fadeFac, 0,255);
		byte b = constrain(blue() + toAdd.blue()*fadeFac, 0,255);
		
		setRGB(r,g,b);
	}
}

void Color::add(Color toAdd){
	byte r = constrain(red() + toAdd.red(), 0,255);
	byte g = constrain(green() + toAdd.green(), 0,255);
	byte b = constrain(blue() + toAdd.blue(), 0,255);
	setRGB(r,g,b);
}

void Color::addHDR(Color toAdd, float fadeFac){
	if(fadeFac!=0.){
		int r = red() + toAdd.red()*fadeFac;
		int g = green() + toAdd.green()*fadeFac;
		int b = blue() + toAdd.blue()*fadeFac;
		
		int maxVal = r;
		if( g > maxVal ) maxVal = g;
		if( b > maxVal ) maxVal = b;
		
		if( maxVal > 255){
			float mult = 255./maxVal;
			r *= mult;
			g *= mult;
			b *= mult;
		}
		
		setRGB(r,g,b);
	}
}

void Color::multiply(Color toMult, float fadeFac){
	if(fadeFac!=0.){
		byte r = red();
		byte g = green();
		byte b = blue();
		
		if(toMult.red()!=255) r = r * (toMult.red()+(255-toMult.red())*(1-fadeFac)) / 255;
		if(toMult.green()!=255) g = g * (toMult.green()+(255-toMult.green())*(1-fadeFac)) / 255;
		if(toMult.blue()!=255) b = b * (toMult.blue()+(255-toMult.blue())*(1-fadeFac)) / 255;
		
		setRGB(r,g,b);
	}
}

void Color::multiply(Color toMult){
	byte r = red();
	byte g = green();
	byte b = blue();
	
	if(toMult.red()!=255) r = r * toMult.red() / 255.;
	if(toMult.green()!=255) g = g * toMult.green() / 255.;
	if(toMult.blue()!=255) b = b * toMult.blue() / 255.;
	
	setRGB(r,g,b);
}

void Color::multiply(float multFac){
	if(multFac!=1.){
		byte r = red()*multFac;
		byte g = green()*multFac;
		byte b = blue()*multFac;
		setRGB(r,g,b);
	}
}

void Color::fade(Color toFade, float fadeFac){
	if(fadeFac==1.){
		setRGB(toFade.red(),toFade.green(),toFade.blue());
	}else if(fadeFac!=0.){
		byte r = constrain(red()*(1-fadeFac) + toFade.red()*fadeFac, 0,255);
		byte g = constrain(green()*(1-fadeFac) + toFade.green()*fadeFac, 0,255);
		byte b = constrain(blue()*(1-fadeFac) + toFade.blue()*fadeFac, 0,255);
		
		setRGB(r,g,b);
	}
}

void Color::fade(Color c1, Color c2, float fadeFac){
	setRGB(c1.red(),c1.green(),c1.blue());
	fade(c2, fadeFac);
}

//// convert hsb to rgb
RGB Color::HSBtoRGB(HSB *color){
  RGB output;
  int hue = color->h%360;
  byte bri = min(color->b,100)*2.55;
  if (color->s == 0) { // Acromatic color (gray). Hue doesn't mind.
    output.r=bri;
    output.g=bri;
    output.b=bri;  
  }
  else{
    byte base = ((255 - int(min(color->s,100)*2.55)) * bri)>>8;

    switch(hue/60) {
    case 0:
      output.r = bri;
      output.g = (((bri-base)*hue)/60)+base;
      output.b = base;
      break;

    case 1:
      output.r = (((bri-base)*(60-(hue%60)))/60)+base;
      output.g = bri;
      output.b = base;
      break;

    case 2:
      output.r = base;
      output.g = bri;
      output.b = (((bri-base)*(hue%60))/60)+base;
      break;

    case 3:
      output.r = base;
      output.g = (((bri-base)*(60-(hue%60)))/60)+base;
      output.b = bri;
      break;

    case 4:
      output.r = (((bri-base)*(hue%60))/60)+base;
      output.g = base;
      output.b = bri;
      break;

    case 5:
      output.r = bri;
      output.g = base;
      output.b = (((bri-base)*(60-(hue%60)))/60)+base;
      break;
    }
  }
  return output;
}

HSB Color::RGBtoHSB(RGB *color){
  byte max_rgb = max(max(color->r,color->g), color->b);
  byte min_rgb = min(min(color->r,color->g), color->b);
  
  HSB output;
  output.s = max_rgb - min_rgb;

  if (output.s == 0) output.h = 0;
  else if (max_rgb == color->r){
    if(color->b>color->g) output.h = 360+(0 + (float)(color->g-color->b) /  output.s) * 60;
    else output.h = (0 + (float)(color->g-color->b) /  output.s) * 60;
  } 
  else if (max_rgb == color->g) output.h = (2 + (float)(color->b-color->r) /  output.s) * 60;
  else if (max_rgb == color->b) output.h = (4 + (float)(color->r-color->g) /  output.s) * 60;

  output.s = (float)output.s/max_rgb*100;
  output.b = max_rgb/2.55;

  return output;
}