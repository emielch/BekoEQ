
bool jackInOn = true;
bool USBInOn = true;
bool speakerOn = true;

float batVolt = 0;


String labelScreenBri ="";

void setScreenBri(int s) {
	if (s < 5) screenBri = 5;
	else if (s > 255) screenBri = 255;
	else screenBri = s;
	gui.setScreenBri(screenBri);
	labelScreenBri = String(screenBri / 2.55, 0) + "%";
}

void moveScreenBri(float b, void* page) {
	if (b > 0 && b < 1) b = 1;
	setScreenBri(screenBri + b);
	scheduleSettingsSave();
}

elapsedMillis timeSinceBatRead = 0;
void updateBatVolt() {
	if (timeSinceBatRead > 100) {
		timeSinceBatRead -= 100;
		float newBatVolt = (analogRead(BAT_SENSE) / 4096.) * 3.3 * 2 - 0.84;
		batVolt = batVolt * 0.9 + newBatVolt * 0.1;
	}
}

String jackLabels[] = { "Auto","On","Off" };
String labelJackIn = jackLabels[jackSetting];
void setJackSetting(int s) {
	jackSetting = constrain(s, 0, 2);
	labelJackIn = jackLabels[jackSetting];

	if (jackSetting == 1) jackInOn = true;
	if (jackSetting == 2) jackInOn = false;
}

void moveJackIn(float b, void* page)
{
	setJackSetting(jackSetting + posOrNeg(b));
	scheduleSettingsSave();
}

String USBLabels[] = { "On","Off" };
String labelUSBIn = USBLabels[usbSetting];
void setUSBSetting(int s) {
	usbSetting = constrain(s, 0, 1);
	labelUSBIn = USBLabels[usbSetting];

	if (usbSetting == 0) USBInOn = true;
	else USBInOn = false;
}

void moveUSBIn(float b, void* page)
{
	setUSBSetting(usbSetting + posOrNeg(b));
	scheduleSettingsSave();
}

String speakerLabels[] = { "On","Off" };
String labelSpeaker = speakerLabels[speakerSetting];
void setSpeakerSetting(int s) {
	speakerSetting = constrain(s, 0, 1);
	labelSpeaker = speakerLabels[speakerSetting];

	if (speakerSetting == 0) {
		speakerOn = true;
		digitalWrite(SPEAKER_ENABLE, HIGH);
	}
	else {
		speakerOn = false;
		digitalWrite(SPEAKER_ENABLE, LOW);
	}
}

void moveSpeakerOut(float b, void* page)
{
	setSpeakerSetting(speakerSetting + posOrNeg(b));
	scheduleSettingsSave();
}

int posOrNeg(float in) {
	if (in > 0)return 1;
	return -1;
}
