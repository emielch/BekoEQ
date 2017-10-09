#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=145,352
AudioInputUSB            usb1;           //xy=147,306
AudioMixer4              mixer4;         //xy=391,351
AudioMixer4              mixer5;         //xy=392,426
AudioSynthWaveformDc     inputMult;            //xy=395,494
AudioEffectMultiply      multiply1;      //xy=602,329
AudioEffectMultiply      multiply2;      //xy=603,484
AudioFilterBiquad        biquad2;        //xy=745,485
AudioFilterBiquad        biquad1;        //xy=757,329
AudioFilterStateVariable filter3;        //xy=916,521
AudioFilterStateVariable filter4;        //xy=918,573
AudioFilterStateVariable filter1;        //xy=919,359
AudioFilterStateVariable filter2;        //xy=920,417
AudioMixer4              mixer3;         //xy=1060,202
AudioMixer4              mixer1;         //xy=1071,347
AudioMixer4              mixer2;         //xy=1074,506
AudioOutputI2S           i2s2;           //xy=1269,413
AudioConnection          patchCord1(i2s1, 0, mixer4, 0);
AudioConnection          patchCord2(i2s1, 1, mixer5, 1);
AudioConnection          patchCord3(usb1, 0, mixer4, 1);
AudioConnection          patchCord4(usb1, 1, mixer5, 0);
AudioConnection          patchCord5(mixer4, 0, multiply1, 0);
AudioConnection          patchCord6(mixer5, 0, multiply2, 0);
AudioConnection          patchCord7(inputMult, 0, multiply1, 1);
AudioConnection          patchCord8(inputMult, 0, multiply2, 1);
AudioConnection          patchCord9(multiply1, biquad1);
AudioConnection          patchCord10(multiply2, biquad2);
AudioConnection          patchCord11(biquad2, 0, mixer2, 0);
AudioConnection          patchCord12(biquad2, 0, filter3, 0);
AudioConnection          patchCord13(biquad2, 0, filter4, 0);
AudioConnection          patchCord14(biquad1, 0, filter1, 0);
AudioConnection          patchCord15(biquad1, 0, filter2, 0);
AudioConnection          patchCord16(biquad1, 0, mixer1, 0);
AudioConnection          patchCord17(filter3, 0, mixer3, 2);
AudioConnection          patchCord18(filter3, 1, mixer2, 1);
AudioConnection          patchCord19(filter4, 0, mixer3, 3);
AudioConnection          patchCord20(filter4, 1, mixer2, 2);
AudioConnection          patchCord21(filter1, 0, mixer3, 0);
AudioConnection          patchCord22(filter1, 1, mixer1, 1);
AudioConnection          patchCord23(filter2, 0, mixer3, 1);
AudioConnection          patchCord24(filter2, 1, mixer1, 2);
AudioConnection          patchCord25(mixer1, 0, i2s2, 0);
AudioConnection          patchCord26(mixer2, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=528,90
										 // GUItool: end automatically generated code


float lowShelfFreq = 200;
float band1Freq = 500;
float band2Freq = 2000;
float highShelfFreq = 7000;

float lowShelfGain = 0;
float band1Gain = 0;
float band2Gain = 0;
float highShelfGain = 0;

float lowShelfQ = 1;
float band1Q = 0.7;
float band2Q = 0.7;
float highShelfQ = 1;



void setupAudio() {
	AudioMemory(80);
	inputMult.amplitude(0.4);

	sgtl5000_1.enable();  // Enable the audio shield
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.volume(0.8);

	updateLowShelf();
	updateBand1();
	updateBand2();
	updateHighShelf();
}

void updateLowShelf() {
	biquad1.setLowShelf(0, lowShelfFreq, lowShelfGain, lowShelfQ);
	biquad2.setLowShelf(0, lowShelfFreq, lowShelfGain, lowShelfQ);
}

void updateBand1() {
	filter1.frequency(band1Freq);
	filter1.resonance(band1Q);
	mixer1.gain(1, band1Gain);

	filter3.frequency(band1Freq);
	filter3.resonance(band1Q);
	mixer2.gain(1, band1Gain);

	/*biquad1.setNotch(2, band1Freq, band1Q);
	biquad2.setNotch(2, band1Freq, band1Q);*/
}

void updateBand2() {
	filter2.frequency(band2Freq);
	filter2.resonance(band2Q);
	mixer1.gain(2, band2Gain);

	filter4.frequency(band2Freq);
	filter4.resonance(band2Q);
	mixer2.gain(2, band2Gain);

	/*biquad1.setNotch(3, band2Freq, band2Q);
	biquad2.setNotch(3, band2Freq, band2Q);*/
}

void updateHighShelf() {
	biquad1.setHighShelf(1, highShelfFreq, highShelfGain, highShelfQ);
	biquad2.setHighShelf(1, highShelfFreq, highShelfGain, highShelfQ);
}


// FREQ
void setLowShelfFreq(float freq) {
	lowShelfFreq += lowShelfFreq*0.03*freq;
	if (lowShelfFreq < 0.1)lowShelfFreq = 0.1;
	else if (lowShelfFreq > 22050)lowShelfFreq = 22050;
	updateLowShelf();
}

void setBand1Freq(float freq) {
	band1Freq += band1Freq*0.03*freq;;
	if (band1Freq < 0.1)band1Freq = 0.1;
	else if (band1Freq > 22050)band1Freq = 22050;
	updateBand1();
}

void setBand2Freq(float freq) {
	band2Freq += band2Freq*0.03*freq;;
	if (band2Freq < 0.1)band2Freq = 0.1;
	else if (band2Freq > 22050)band2Freq = 22050;
	updateBand2();
}

void setHighShelfFreq(float freq) {
	highShelfFreq += highShelfFreq*0.03*freq;;
	if (highShelfFreq < 0.1)highShelfFreq = 0.1;
	else if (highShelfFreq > 22050)highShelfFreq = 22050;
	updateHighShelf();
}

// GAIN
void setLowShelfGain(float gain) {
	lowShelfGain += gain*0.3;
	updateLowShelf();
}

void setBand1Gain(float gain) {
	band1Gain += gain*0.3;
	if (band1Gain < 0)band1Gain = 0;
	else if (band1Gain > 20)band1Gain = 20;
	updateBand1();
}

void setBand2Gain(float gain) {
	band2Gain += gain*0.3;
	if (band2Gain < 0)band2Gain = 0;
	else if (band2Gain > 20)band2Gain = 20;
	updateBand2();
}

void setHighShelfGain(float gain) {
	highShelfGain += gain*0.3;
	updateHighShelf();
}


// Q
void setLowShelfQ(float q) {
	lowShelfQ += q*0.3;
	updateLowShelf();
}

void setBand1Q(float q) {
	band1Q += q*0.3;
	if (band1Q < 0.7)band1Q = 0.7;
	else if (band1Q > 5)band1Q = 5;
	updateBand1();
}

void setBand2Q(float q) {
	band2Q += q*0.3;
	if (band2Q < 0.7)band2Q = 0.7;
	else if (band2Q > 5)band2Q = 5;
	updateBand2();
}

void setHighShelfQ(float q) {
	highShelfQ += q*0.3;
	updateHighShelf();
}