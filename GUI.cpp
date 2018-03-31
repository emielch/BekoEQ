// 
// 
// 

#include "GUI.h"

GUI::GUI() {
	GUIPage::begin("GUI", 0, 0);
	tft.begin();
	tft.setRotation(0);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextWrap(false);
	tft.setTextSize(2);
	pinMode(BACKLIGHT, OUTPUT);
	analogWrite(BACKLIGHT, backlightPower);
	screenSwitch(true);
	tft.fillScreen(ILI9341_BLACK);

	notifyBar.begin(0, 20, Color(0, 20, 50, HSB_MODE));
	navBar.begin(this, 0, 20, tft.width(), 30, Color(0, 0, 50, HSB_MODE));
	topBarHeight = 20 + navBar.getHeight();
	testPage.begin(0, topBarHeight);
	settingsPage.begin(0, topBarHeight);
	pages[0] = &testPage;
	pages[1] = &settingsPage;
	navBar.setPages(pages, pageAm);

	testPage.setTopElem(&navBar);
	settingsPage.setTopElem(&navBar);

	switchPage(&testPage);
}

void GUI::screenSwitch(bool on)
{
	screenOn = on;
}

void GUI::setScreenBri(int bri)
{
	screenBri = bri;
	analogWrite(BACKLIGHT, backlightPower*screenBri);
}

void GUI::update()
{
	if (screenOn) {
		if (backlightPower < 1) {
			backlightPower += 0.0001;
			analogWrite(BACKLIGHT, backlightPower*screenBri);
		}
		if (millis() > lastInput + 8000) screenSwitch(false);
		currentPage->update();
		notifyBar.update();
		navBar.update();
	}
	else {
		if (backlightPower > 0) {
			backlightPower -= 0.0001;
			analogWrite(BACKLIGHT, backlightPower*screenBri);
		}
	}
}

void GUI::draw()
{
	notifyBar.draw(tft);
	navBar.draw(tft);
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
	currentPage = page;
	currentPage->setTopElem(&navBar);
	currentPage->setSelectedElem(&navBar);
	navBar.select();
	currentPage->resetDrawing();
}


