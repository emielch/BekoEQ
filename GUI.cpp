// 
// 
// 

#include "GUI.h"

GUI::GUI() {
	GUIPage::begin("GUI", 0, 0, tft.width(), tft.height());
	tft.begin();
	tft.setRotation(0);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextWrap(false);
	tft.setTextSize(2);
	pinMode(BACKLIGHT, OUTPUT);
	setBacklightPower(1);
	tft.fillScreen(ILI9341_BLACK);

	topBarHeight = 0;
	notifyBar.begin(0, 25, Color(100, 0, 60, HSB_MODE));
	audioLevelLeft.begin(0, topBarHeight += notifyBar.getHeight() + 1, tft.width(), 3, Color(0, 0, 0, RGB_MODE));
	audioLevelRight.begin(0, topBarHeight += audioLevelLeft.getHeight() + 1, tft.width(), 3, Color(0, 0, 0, RGB_MODE));
	navBar.begin(this, 0, topBarHeight += audioLevelRight.getHeight() + 1, tft.width(), 30, Color(220, 20, 30, HSB_MODE));
	topBarHeight += navBar.getHeight();

	settingsPage.begin(0, topBarHeight, tft.width(), tft.height() - topBarHeight);
	eqPage.begin(0, topBarHeight, tft.width(), tft.height() - topBarHeight);

	pages[0] = &settingsPage;
	pages[1] = &eqPage;
	navBar.setPages(pages, pageAm);

	settingsPage.setTopElem(&navBar);
	eqPage.setTopElem(&navBar);

	audioLevelLeft.setSource(&peakOutLeftVal);
	audioLevelRight.setSource(&peakOutRightVal);

	navBar.goToPageIndex(1);
}

void GUI::setBacklightPower(float val)
{
	backlightPowerSetpoint = val;
}

void GUI::setScreenBri(int bri)
{
	screenBri = bri;
	//analogWrite(BACKLIGHT, backlightPower*screenBri);
}

void GUI::update(float dt)
{
	updateScreenBri(dt);

	if (backlightPower > 0.01) {
		currentPage->update();
		notifyBar.update();
		navBar.update();
		audioLevelLeft.update(dt);
		audioLevelRight.update(dt);
	}
}

void GUI::updateScreenBri(float dt)
{
	if (backlightPowerSetpoint == 1) {
		if (millis() > lastInput + 10000) setBacklightPower(0.05);
	}
	else if (backlightPowerSetpoint > 0) {
		if (millis() > lastInput + 15000) setBacklightPower(0);
	}

	if (backlightPower != backlightPowerSetpoint) {
		if (backlightPowerSetpoint > backlightPower) {
			backlightPower += 0.01*dt;
			if (backlightPower > backlightPowerSetpoint) backlightPower = backlightPowerSetpoint;
		}
		else if (backlightPowerSetpoint < backlightPower) {
			backlightPower -= 0.01*dt;
			if (backlightPower < backlightPowerSetpoint) backlightPower = backlightPowerSetpoint;
		}

		//analogWrite(BACKLIGHT, ceil(backlightPower*screenBri));

		if (backlightPower>0.01) {
			digitalWrite(BACKLIGHT, false);
			pinMode(BACKLIGHT, OUTPUT);
		}
		else {
			digitalWrite(BACKLIGHT, false);
			pinMode(BACKLIGHT, INPUT);
		}
	}
}

void GUI::draw()
{
	notifyBar.draw(tft);
	navBar.draw(tft);
	audioLevelLeft.draw(tft);
	audioLevelRight.draw(tft);
	currentPage->draw(tft);
}

bool GUI::inputBlock()
{
	lastInput = millis();

	if (backlightPowerSetpoint < 0.01) {
		lastTimeoutInput = lastInput;
	}

	setBacklightPower(1);

	if (lastInput - lastTimeoutInput < 300) {
		lastTimeoutInput = lastInput;
		return true;
	}

	return false;
}

void GUI::inputUp(int val)
{
	if (inputBlock()) return;
	for (int i = 0; i < val; i++) {
		if (!currentPage->inputUp())
			GUIPage::inputUp();
	}

}

void GUI::inputDown(int val)
{
	if (inputBlock()) return;
	for (int i = 0; i < val; i++) {
		if (!currentPage->inputDown())
			GUIPage::inputDown();
	}

}

void GUI::inputLeft(int val)
{
	if (inputBlock()) return;
	for (int i = 0; i < val; i++) {
		if (!currentPage->inputLeft())
			GUIPage::inputLeft();
	}

}

void GUI::inputRight(int val)
{
	if (inputBlock()) return;
	for (int i = 0; i < val; i++) {
		if (!currentPage->inputRight())
			GUIPage::inputRight();
	}

}

void GUI::switchPage(GUIPage* page) {
	currentPage = page;
	currentPage->setTopElem(&navBar);
	currentPage->setSelectedElem(NULL);
	navBar.select();
	currentPage->resetDrawing();
}


