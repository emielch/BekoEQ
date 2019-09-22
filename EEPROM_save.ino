#include <EEPROM.h>

extern EQ_SETTINGS current_EQ_settings;

String saveString = "OK";

struct SETTINGS {
	byte screenBri;
	byte jackSetting;
	byte usbSetting;
	byte speakerSetting;
};

bool settingsSaveIsScheduled = false;
unsigned long nextSettingsSaveTime = 0;

bool eqSaveIsScheduled = false;
unsigned long nextEQSaveTime = 0;


void scheduleSettingsSave() {
	nextSettingsSaveTime = millis() + 2000;
	settingsSaveIsScheduled = true;
}

void scheduleEQSave() {
	nextEQSaveTime = millis() + 2000;
	eqSaveIsScheduled = true;
}

void updateSaving() {
	if (settingsSaveIsScheduled && millis() > nextSettingsSaveTime) {
		settingsSaveIsScheduled = false;
		saveSettings();
	}

	if (eqSaveIsScheduled && millis() > nextEQSaveTime) {
		eqSaveIsScheduled = false;
		saveEQSettings_jack(0);
		saveEQSettings_usb(1);
	}
}

void saveSettings() {
	SETTINGS settings = { screenBri, jackSetting, usbSetting, speakerSetting };
	EEPROM.put(0, settings);
}

void loadSettings() {
	SETTINGS settings;
	EEPROM.get(0, settings);
	setScreenBri(settings.screenBri);
	setJackSetting(settings.jackSetting);
	setUSBSetting(settings.usbSetting);
	setSpeakerSetting(settings.speakerSetting);
}



void saveEQSettings_jack(int idx) {
	int EEPROM_offset = sizeof(SETTINGS) + idx * sizeof(EQ_SETTINGS);
	EEPROM.put(EEPROM_offset, current_jack_EQ_settings);
}

void saveEQSettings_usb(int idx) {
	int EEPROM_offset = sizeof(SETTINGS) + idx * sizeof(EQ_SETTINGS);
	EEPROM.put(EEPROM_offset, current_usb_EQ_settings);
}

void loadEQSettings(int idx, int inputEQ) {
	EQ_SETTINGS eq_settings;
	int EEPROM_offset = sizeof(SETTINGS) + idx*sizeof(EQ_SETTINGS);
	EEPROM.get(EEPROM_offset, eq_settings);

	if (inputEQ == 0) {   // jack EQ
		current_jack_EQ_settings = eq_settings;
		updateAll_jack();
	}else {    // USB EQ
		current_usb_EQ_settings = eq_settings;
		updateAll_usb();
	}
}


String currentPresetSlotName;
int currentSlotIdx = 0;

void switchPresetSlot(float d, void * this_pointer)
{
	if (d > 0)	currentSlotIdx++;
	else currentSlotIdx--;

	if (this_pointer == &gui.eqPage_usb) {
		if (currentSlotIdx == 0) currentSlotIdx = 1;
	}else {
		if (currentSlotIdx == 1) {
			if (d > 0) currentSlotIdx = 2;
			else currentSlotIdx = 0;
		}
	}
	goToPresetSlot(currentSlotIdx);
}

void goToPresetSlot(int idx) {
	currentSlotIdx = constrain(idx, 0, 5);
	if (currentSlotIdx < 2) currentPresetSlotName = "Default";
	else currentPresetSlotName = "Slot " + String(currentSlotIdx-1);
}

void savePresetSlot(float d, void * this_pointer)
{
	if (currentSlotIdx < 2) return;
	if (this_pointer == &gui.eqPage_usb) saveEQSettings_usb(currentSlotIdx);
	else  saveEQSettings_jack(currentSlotIdx);
}

void loadPresetSlot(float d, void * this_pointer)
{
	if (currentSlotIdx < 2) {
		if (this_pointer == &gui.eqPage_usb) {
			current_usb_EQ_settings = { 0,200,1,0,500,0.7,0,2000,0.7,0,7000,1 };
			updateAll_usb();
		} else {
			current_jack_EQ_settings = { 0,200,1,0,500,0.7,0,2000,0.7,0,7000,1 };
			updateAll_jack();
		}
	}
	else {
		if(this_pointer== &gui.eqPage_usb) loadEQSettings(currentSlotIdx,1);
		else loadEQSettings(currentSlotIdx,0);
	}
}


void updateAll_usb() {
	updateLowShelf_usb();
	updateBand1_usb();
	updateBand2_usb();
	updateHighShelf_usb();
}

void updateAll_jack() {
	updateLowShelf_jack();
	updateBand1_jack();
	updateBand2_jack();
	updateHighShelf_jack();
}
