// 
// 
// 

#include "NotifyBar.h"


NotifyBar::NotifyBar()
{
}

void NotifyBar::begin(int _yPos, int _height, Color _col)
{
	yPos = _yPos;
	height = _height;
	color = _col;
}

int NotifyBar::getHeight() {
	return height;
}

void NotifyBar::update()
{
	if (jackInOn!=_jackInOn || USBInOn != _USBInOn || speakerOn != _speakerOn) {
		_jackInOn = jackInOn;
		_USBInOn = USBInOn;
		_speakerOn = speakerOn;
		updateDrawing = true;
	}
}

void NotifyBar::draw(ILI9341_t3 tft)
{
	if (updateDrawing) {
		tft.fillRect(0, yPos, tft.width(), height, color.getInt());

		if (jackInOn) {
			tft.fillCircle(30, yPos+10, 10, ILI9341_BLUE);
		}
		if (USBInOn) {
			tft.fillCircle(70, yPos+10, 10, ILI9341_CYAN);
		}
		if (speakerOn) {
			tft.fillCircle(110, yPos+10, 10, ILI9341_MAGENTA);
		}

		updateDrawing = false;
	}
}
