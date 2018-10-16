#include <EEPROM.h>

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
		saveEQSettings(0);
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



void saveEQSettings(int idx) {
	int EEPROM_offset = sizeof(SETTINGS) + idx * sizeof(EQ_SETTINGS);
	EEPROM.put(EEPROM_offset, current_EQ_settings);
}

void loadEQSettings(int idx) {
	EQ_SETTINGS eq_settings;
	int EEPROM_offset = sizeof(SETTINGS) + idx*sizeof(EQ_SETTINGS);
	EEPROM.get(EEPROM_offset, eq_settings);
	current_EQ_settings = eq_settings;

	updateLowShelf();
	updateBand1();
	updateBand2();
	updateHighShelf();
}


String currentPresetSlotName;
int currentSlotIdx = 0;

void switchPresetSlot(float d, void * this_pointer)
{
	if (d > 0)	goToPresetSlot(currentSlotIdx + 1);
	else goToPresetSlot(currentSlotIdx - 1);
}

void goToPresetSlot(int idx) {
	currentSlotIdx = constrain(idx, 0, 4);
	if (currentSlotIdx == 0) currentPresetSlotName = "Default";
	else currentPresetSlotName = "Slot " + String(currentSlotIdx);
}

void savePresetSlot(float d, void * this_pointer)
{
	if (currentSlotIdx == 0) return;
	saveEQSettings(currentSlotIdx);
}

void loadPresetSlot(float d, void * this_pointer)
{
	if (currentSlotIdx == 0) {
		current_EQ_settings = { 0,200,1,0,500,0.7,0,2000,0.7,0,7000,1 };

		updateLowShelf();
		updateBand1();
		updateBand2();
		updateHighShelf();
	}
	else {
		loadEQSettings(currentSlotIdx);
	}
}

