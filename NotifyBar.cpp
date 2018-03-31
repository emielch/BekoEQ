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

void NotifyBar::update()
{

}

void NotifyBar::draw(ILI9341_t3 tft)
{
	if (!updateDrawing) return;

	int bgColor = color.getInt();

	tft.fillRect(0, yPos, tft.width(), height, bgColor);

	updateDrawing = false;
}
