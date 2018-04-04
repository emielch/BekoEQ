// 
// 
// 

#include "NotifyBar.h"
#include "icons.h"


NotifyBar::NotifyBar()
{
}

void NotifyBar::begin(int _yPos, int _height, Color _col)
{
	yPos = _yPos;
	height = _height;
	color = _col;

	_batteryOn = true;
}

int NotifyBar::getHeight() {
	return height;
}

void NotifyBar::update()
{
	if (jackInOn != _jackInOn || USBInOn != _USBInOn || speakerOn != _speakerOn) {
		_jackInOn = jackInOn;
		_USBInOn = USBInOn;
		_speakerOn = speakerOn;
		updateDrawing = true;
	}

	int _batVoltRound = batVolt * 100;
	if (_batVoltRound != batVoltRound) {
		batVoltRound = _batVoltRound;
		updateBatVoltTxt = true;
	}
}


void NotifyBar::draw(ILI9341_t3 tft)
{
	if (updateDrawing) {
		tft.fillRect(0, yPos, tft.width(), height, color.getInt());
		updateBatVoltTxt = true;
		int yOffset = 2;

		int iconCol;
		int offCol = Color(color.hue(), color.saturation(), color.brightness() - 20, HSB_MODE).getInt();
		int onColor = ILI9341_BLACK;

		if (_jackInOn) iconCol = onColor;
		else iconCol = offCol;
		tft.drawBitmap(5, yPos + yOffset, jackIcon, 24, 24, iconCol);

		if (_USBInOn) iconCol = onColor;
		else iconCol = offCol;
		tft.drawBitmap(28, yPos + yOffset, USBIcon, 24, 24, iconCol);

		if (_speakerOn) iconCol = onColor;
		else iconCol = offCol;
		tft.drawBitmap(56, yPos + yOffset, speakerIcon, 24, 24, iconCol);

		if (_batteryOn) iconCol = onColor;
		else iconCol = offCol;
		tft.drawBitmap(tft.width()-25, yPos + yOffset, batteryIcon, 24, 24, iconCol);

		updateDrawing = false;
	}

	if (updateBatVoltTxt) {
		int xText = tft.width() - 70;

		String printText = String(batVoltRound/100.) + "V";

		tft.fillRect(xText, yPos, 40, height, color.getInt());
		tft.setFont(Arial_12_Bold);
		tft.setTextColor(ILI9341_BLACK);
		tft.setCursor(xText, yPos + 7);
		tft.println(printText);

		updateBatVoltTxt = false;
	}

	
}
