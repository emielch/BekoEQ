
bool jackInOn = true;
bool USBInOn = true;
bool speakerOn = true;

float batVolt = 0;


int screenBri = 20;
String labelScreenBri = String(screenBri / 2.55, 0) + "%";

void setScreenBri(float b) {
	if (b > 0 && b < 1) b = 1;
	screenBri += b;
	if (screenBri < 5) screenBri = 5;
	else if (screenBri > 255) screenBri = 255;
	gui.setScreenBri(screenBri);
	labelScreenBri = String(screenBri / 2.55, 0) + "%";
}

elapsedMillis timeSinceBatRead = 0;
void updateBatVolt() {
	if (timeSinceBatRead > 100) {
		timeSinceBatRead -= 100;
		float newBatVolt = (analogRead(BAT_SENSE) / 4096.) * 3.3 * 2 - 0.84;
		batVolt = batVolt * 0.9 + newBatVolt * 0.1;
	}
}


int jackSetting = 0;
String jackLabels[] = { "Auto","On","Off" };
String labelJackIn = jackLabels[jackSetting];
void setJackIn(float b)
{
	jackSetting += posOrNeg(b);
	jackSetting = constrain(jackSetting, 0, 2);
	labelJackIn = jackLabels[jackSetting];

	if (jackSetting == 1) jackInOn = true;
	if (jackSetting == 2) jackInOn = false;
}

int USBSetting = 0;
String USBLabels[] = { "On","Off" };
String labelUSBIn = USBLabels[USBSetting];
void setUSBIn(float b)
{
	USBSetting += posOrNeg(b);
	USBSetting = constrain(USBSetting, 0, 1);
	labelUSBIn = USBLabels[USBSetting];

	if (USBSetting == 0) USBInOn = true;
	else USBInOn = false;
}

int speakerSetting = 1;
String speakerLabels[] = { "On","Off" };
String labelSpeaker = speakerLabels[speakerSetting];
void setSpeaker(float b)
{
	speakerSetting += posOrNeg(b);
	speakerSetting = constrain(speakerSetting, 0, 1);
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

int posOrNeg(float in) {
	if (in > 0)return 1;
	return -1;
}
