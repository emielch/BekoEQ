#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=195,367
AudioInputUSB            usb_in;         //xy=197,321
AudioOutputUSB           usb_out;        //xy=311,502
AudioAnalyzeRMS          rms1;           //xy=333.0000190734863,631.0000381469727
AudioMixer4              mixer4;         //xy=441,366
AudioMixer4              mixer5;         //xy=442,441
AudioSynthWaveformDc     inputMult;      //xy=445,509
AudioEffectMultiply      multiply1;      //xy=652,344
AudioEffectMultiply      multiply2;      //xy=653,499
AudioFilterBiquad        biquad2;        //xy=795,500
AudioFilterBiquad        biquad1;        //xy=807,344
AudioFilterStateVariable filter3;        //xy=966,536
AudioFilterStateVariable filter4;        //xy=968,588
AudioFilterStateVariable filter1;        //xy=969,374
AudioFilterStateVariable filter2;        //xy=970,432
AudioMixer4              mixer3;         //xy=1110,217
AudioMixer4              mixer1;         //xy=1121,362
AudioMixer4              mixer2;         //xy=1124,521
AudioOutputI2S           i2s2;           //xy=1319,428
AudioAnalyzePeak         peakOut_left;          //xy=1324.0000762939453,351.00002098083496
AudioAnalyzePeak         peakOut_right;          //xy=1327.0000762939453,523.0000324249268
AudioConnection          patchCord1(i2s1, 0, mixer4, 0);
AudioConnection          patchCord2(i2s1, 0, usb_out, 0);
AudioConnection          patchCord3(i2s1, 1, usb_out, 1);
AudioConnection          patchCord4(i2s1, 1, mixer5, 0);
AudioConnection          patchCord5(i2s1, 1, rms1, 0);
AudioConnection          patchCord6(usb_in, 0, mixer4, 1);
AudioConnection          patchCord7(usb_in, 1, mixer5, 1);
AudioConnection          patchCord8(mixer4, 0, multiply1, 0);
AudioConnection          patchCord9(mixer5, 0, multiply2, 0);
AudioConnection          patchCord10(inputMult, 0, multiply1, 1);
AudioConnection          patchCord11(inputMult, 0, multiply2, 1);
AudioConnection          patchCord12(multiply1, biquad1);
AudioConnection          patchCord13(multiply2, biquad2);
AudioConnection          patchCord14(biquad2, 0, mixer2, 0);
AudioConnection          patchCord15(biquad2, 0, filter3, 0);
AudioConnection          patchCord16(biquad2, 0, filter4, 0);
AudioConnection          patchCord17(biquad1, 0, filter1, 0);
AudioConnection          patchCord18(biquad1, 0, filter2, 0);
AudioConnection          patchCord19(biquad1, 0, mixer1, 0);
AudioConnection          patchCord20(filter3, 0, mixer3, 2);
AudioConnection          patchCord21(filter3, 1, mixer2, 1);
AudioConnection          patchCord22(filter4, 0, mixer3, 3);
AudioConnection          patchCord23(filter4, 1, mixer2, 2);
AudioConnection          patchCord24(filter1, 0, mixer3, 0);
AudioConnection          patchCord25(filter1, 1, mixer1, 1);
AudioConnection          patchCord26(filter2, 0, mixer3, 1);
AudioConnection          patchCord27(filter2, 1, mixer1, 2);
AudioConnection          patchCord28(mixer1, 0, i2s2, 0);
AudioConnection          patchCord29(mixer1, peakOut_left);
AudioConnection          patchCord30(mixer2, 0, i2s2, 1);
AudioConnection          patchCord31(mixer2, peakOut_right);
AudioControlSGTL5000     sgtl5000_1;     //xy=578,105
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

unsigned long lastNoiseThresh = 0;
float jackIn_gain = 1;

float USBIn_gain = 1;

float peakOutLeftVal = 0;
float peakOutRightVal = 0;


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

void updateAudio(float dt) {
	if (peakOut_left.available() && peakOut_right.available()) {
		peakOutLeftVal = peakOut_left.read();
		peakOutRightVal = peakOut_right.read();
	}

	if (rms1.available() && jackSetting == 0) {
		float rms_val = rms1.read() * 1000;
		if (rms_val > 2.0) {
			lastNoiseThresh = millis();
			if (!jackInOn) jackInOn = true;
		}
		if (millis() - lastNoiseThresh > 5000 && jackInOn) jackInOn = false;
	}

	if (jackInOn && jackIn_gain < 1.0) {
		jackIn_gain += 0.01*dt;
		updateInputGain(0, jackIn_gain);
	}
	else if (!jackInOn && jackIn_gain > 0.0) {
		jackIn_gain -= 0.01*dt;
		updateInputGain(0, jackIn_gain);
	}

	float usb_vol = usb_in.volume()*10;
	if (USBInOn && USBIn_gain < 1.0) {
		USBIn_gain += 0.01*dt;
	}
	else if (!USBInOn && USBIn_gain > 0.0) {
		USBIn_gain -= 0.01*dt;
	}
	updateInputGain(1, USBIn_gain*usb_vol);
}

void updateInputGain(int channel, float val) {
	mixer4.gain(channel, val);
	mixer5.gain(channel, val);
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
void setLowShelfFreq(float freq, void* page) {
	lowShelfFreq += lowShelfFreq * 0.03 * freq;
	if (lowShelfFreq < 0.1)lowShelfFreq = 0.1;
	else if (lowShelfFreq > 22050)lowShelfFreq = 22050;
	updateLowShelf();
}

void setBand1Freq(float freq, void* page) {
	band1Freq += band1Freq * 0.03 * freq;;
	if (band1Freq < 0.1)band1Freq = 0.1;
	else if (band1Freq > 22050)band1Freq = 22050;
	updateBand1();
}

void setBand2Freq(float freq, void* page) {
	band2Freq += band2Freq * 0.03 * freq;;
	if (band2Freq < 0.1)band2Freq = 0.1;
	else if (band2Freq > 22050)band2Freq = 22050;
	updateBand2();
}

void setHighShelfFreq(float freq, void* page) {
	highShelfFreq += highShelfFreq * 0.03 * freq;;
	if (highShelfFreq < 0.1)highShelfFreq = 0.1;
	else if (highShelfFreq > 22050)highShelfFreq = 22050;
	updateHighShelf();
}

// GAIN
void setLowShelfGain(float gain, void* page) {
	lowShelfGain += gain * 0.3;
	updateLowShelf();
}

void setBand1Gain(float gain, void* page) {
	band1Gain += gain * 0.3;
	if (band1Gain < 0)band1Gain = 0;
	else if (band1Gain > 20)band1Gain = 20;
	updateBand1();
}

void setBand2Gain(float gain, void* page) {
	band2Gain += gain * 0.3;
	if (band2Gain < 0)band2Gain = 0;
	else if (band2Gain > 20)band2Gain = 20;
	updateBand2();
}

void setHighShelfGain(float gain, void* page) {
	highShelfGain += gain * 0.3;
	updateHighShelf();
}


// Q
void setLowShelfQ(float q, void* page) {
	lowShelfQ += q * 0.3;
	updateLowShelf();
}

void setBand1Q(float q, void* page) {
	band1Q += q * 0.3;
	if (band1Q < 0.7)band1Q = 0.7;
	else if (band1Q > 5)band1Q = 5;
	updateBand1();
}

void setBand2Q(float q, void* page) {
	band2Q += q * 0.3;
	if (band2Q < 0.7)band2Q = 0.7;
	else if (band2Q > 5)band2Q = 5;
	updateBand2();
}

void setHighShelfQ(float q, void* page) {
	highShelfQ += q * 0.3;
	updateHighShelf();
}
