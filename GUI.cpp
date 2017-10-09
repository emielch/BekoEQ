// 
// 
// 

#include "GUI.h"

GUI::GUI() {
	tft.begin();
	tft.setRotation(0);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextWrap(false);
	tft.setTextSize(2);
	screenSwitch(true);
	tft.fillScreen(ILI9341_BLACK);


	switchPage(&testPage);
}

void GUI::screenSwitch(bool on)
{
	if (on) {
		digitalWrite(BACKLIGHT, false);
		pinMode(BACKLIGHT, OUTPUT);
	}
	else {
		digitalWrite(BACKLIGHT, false);
		pinMode(BACKLIGHT, INPUT);
	}
	screenOn = on;
}

void GUI::update()
{
	if (screenOn) {
		if (millis() > lastInput + 8000) screenSwitch(false);
		currentPage->update();
	}
}

void GUI::draw()
{
	currentPage->draw(tft);
}

bool GUI::inputBlock()
{
	lastInput = millis();
	if (!screenOn) {
		screenSwitch(true);
		lastTimeoutInput = lastInput;
	}

	if (lastInput - lastTimeoutInput < 300) {
		lastTimeoutInput = lastInput;
		return true;
	}

	return !screenOn;
}

void GUI::inputUp(int val)
{
	if (inputBlock()) return;
	for (int i = 0; i < val; i++) {
		currentPage->inputUp();
	}
}

void GUI::inputDown(int val)
{
	if (inputBlock()) return;
	for (int i = 0; i < val; i++) {
		currentPage->inputDown();
	}
}

void GUI::inputLeft(int val)
{
	if (inputBlock()) return;
	for (int i = 0; i < val; i++) {
		currentPage->inputLeft();
	}
}

void GUI::inputRight(int val)
{
	if (inputBlock()) return;
	for (int i = 0; i < val; i++) {
		currentPage->inputRight();
	}
}

void GUI::switchPage(GUIPage* page) {
	tft.fillScreen(ILI9341_BLACK);
	currentPage = page;
	currentPage->draw(tft, true);
}


