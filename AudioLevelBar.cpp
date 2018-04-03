// 
// 
// 

#include "AudioLevelBar.h"

AudioLevelBar::AudioLevelBar()
{
}

void AudioLevelBar::begin(int _xPos, int _yPos, int _width, int _height, Color _bgColor)
{
	xPos = _xPos;
	yPos = _yPos;
	width = _width;
	height = _height;
	bgColor = _bgColor;
}

void AudioLevelBar::setSource(float * _source)
{
	floatSource = _source;
}

int AudioLevelBar::getHeight()
{
	return height;;
}

void AudioLevelBar::update(float dt)
{
	prevMeterVal = meterVal;
	meterVal = max(constrain(1 + 0.5*log10(*floatSource), 0, 1), meterVal -= 0.01*dt);
}

void AudioLevelBar::draw(ILI9341_t3 tft)
{
	float colHue = 340 - meterVal * 350;
	Color barCol = Color(constrain(colHue,0,120), 100, 100, HSB_MODE);

	int meterWidth = width * meterVal;

	tft.fillRect(xPos, yPos, meterWidth, height, barCol.getInt());  // top bar
	if (meterVal < prevMeterVal) {
		int meterDiff = width * prevMeterVal - meterVal;
		tft.fillRect(xPos + meterWidth + 1, yPos, meterDiff, height, bgColor.getInt());  // erase previous audio bars
	}
}
