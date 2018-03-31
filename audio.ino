#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=172,419
AudioInputUSB            usb_in;           //xy=174,373
AudioOutputUSB           usb_out;           //xy=288.00010681152344,554.0001621246338
AudioAnalyzeRMS          rms1;           //xy=299,692
AudioAnalyzePeak         peak1;          //xy=303.0000190734863,632.0000371932983
AudioMixer4              mixer4;         //xy=418,418
AudioMixer4              mixer5;         //xy=419,493
AudioSynthWaveformDc     inputMult;      //xy=422,561
AudioEffectMultiply      multiply1;      //xy=629,396
AudioEffectMultiply      multiply2;      //xy=630,551
AudioFilterBiquad        biquad2;        //xy=772,552
AudioFilterBiquad        biquad1;        //xy=784,396
AudioFilterStateVariable filter3;        //xy=943,588
AudioFilterStateVariable filter4;        //xy=945,640
AudioFilterStateVariable filter1;        //xy=946,426
AudioFilterStateVariable filter2;        //xy=947,484
AudioMixer4              mixer3;         //xy=1087,269
AudioMixer4              mixer1;         //xy=1098,414
AudioMixer4              mixer2;         //xy=1101,573
AudioOutputI2S           i2s2;           //xy=1296,480
AudioConnection          patchCord1(i2s1, 0, mixer4, 0);
AudioConnection          patchCord2(i2s1, 0, usb_out, 0);
AudioConnection          patchCord3(i2s1, 1, usb_out, 1);
AudioConnection          patchCord4(i2s1, 1, mixer5, 0);
AudioConnection          patchCord5(i2s1, 1, peak1, 0);
AudioConnection          patchCord6(i2s1, 1, rms1, 0);
AudioConnection          patchCord7(usb_in, 0, mixer4, 1);
AudioConnection          patchCord8(usb_in, 1, mixer5, 1);
AudioConnection          patchCord9(mixer4, 0, multiply1, 0);
AudioConnection          patchCord10(mixer5, 0, multiply2, 0);
AudioConnection          patchCord11(inputMult, 0, multiply1, 1);
AudioConnection          patchCord12(inputMult, 0, multiply2, 1);
AudioConnection          patchCord13(multiply1, biquad1);
AudioConnection          patchCord14(multiply2, biquad2);
AudioConnection          patchCord15(biquad2, 0, mixer2, 0);
AudioConnection          patchCord16(biquad2, 0, filter3, 0);
AudioConnection          patchCord17(biquad2, 0, filter4, 0);
AudioConnection          patchCord18(biquad1, 0, filter1, 0);
AudioConnection          patchCord19(biquad1, 0, filter2, 0);
AudioConnection          patchCord20(biquad1, 0, mixer1, 0);
AudioConnection          patchCord21(filter3, 0, mixer3, 2);
AudioConnection          patchCord22(filter3, 1, mixer2, 1);
AudioConnection          patchCord23(filter4, 0, mixer3, 3);
AudioConnection          patchCord24(filter4, 1, mixer2, 2);
AudioConnection          patchCord25(filter1, 0, mixer3, 0);
AudioConnection          patchCord26(filter1, 1, mixer1, 1);
AudioConnection          patchCord27(filter2, 0, mixer3, 1);
AudioConnection          patchCord28(filter2, 1, mixer1, 2);
AudioConnection          patchCord29(mixer1, 0, i2s2, 0);
AudioConnection          patchCord30(mixer2, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=555,157
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
bool inputOn = true;
float input_gain = 1;


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

void updateAudio() {
	float usb_vol = usb_in.volume();
	mixer4.gain(1, usb_vol * 2);
	mixer5.gain(1, usb_vol * 2);

	if (rms1.available()) {
		float rms_val = rms1.read() * 1000;
		if (rms_val > 1.0) {
			lastNoiseThresh = millis();
			if (!inputOn) inputOn = true;
		}
		if (millis() - lastNoiseThresh > 20000 && inputOn) inputOn = false;
	}

	if (inputOn) {
		if (input_gain < 1.0) {
			input_gain += 0.0001;
			updateInputGain();
		}
	}
	else {
		if (input_gain > 0.0) {
			input_gain -= 0.0001;
			updateInputGain();
		}
	}
}

void updateInputGain() {
	mixer4.gain(0, input_gain);
	mixer5.gain(0, input_gain);
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
	lowShelfFreq += lowShelfFreq * 0.03 * freq;
	if (lowShelfFreq < 0.1)lowShelfFreq = 0.1;
	else if (lowShelfFreq > 22050)lowShelfFreq = 22050;
	updateLowShelf();
}

void setBand1Freq(float freq) {
	band1Freq += band1Freq * 0.03 * freq;;
	if (band1Freq < 0.1)band1Freq = 0.1;
	else if (band1Freq > 22050)band1Freq = 22050;
	updateBand1();
}

void setBand2Freq(float freq) {
	band2Freq += band2Freq * 0.03 * freq;;
	if (band2Freq < 0.1)band2Freq = 0.1;
	else if (band2Freq > 22050)band2Freq = 22050;
	updateBand2();
}

void setHighShelfFreq(float freq) {
	highShelfFreq += highShelfFreq * 0.03 * freq;;
	if (highShelfFreq < 0.1)highShelfFreq = 0.1;
	else if (highShelfFreq > 22050)highShelfFreq = 22050;
	updateHighShelf();
}

// GAIN
void setLowShelfGain(float gain) {
	lowShelfGain += gain * 0.3;
	updateLowShelf();
}

void setBand1Gain(float gain) {
	band1Gain += gain * 0.3;
	if (band1Gain < 0)band1Gain = 0;
	else if (band1Gain > 20)band1Gain = 20;
	updateBand1();
}

void setBand2Gain(float gain) {
	band2Gain += gain * 0.3;
	if (band2Gain < 0)band2Gain = 0;
	else if (band2Gain > 20)band2Gain = 20;
	updateBand2();
}

void setHighShelfGain(float gain) {
	highShelfGain += gain * 0.3;
	updateHighShelf();
}


// Q
void setLowShelfQ(float q) {
	lowShelfQ += q * 0.3;
	updateLowShelf();
}

void setBand1Q(float q) {
	band1Q += q * 0.3;
	if (band1Q < 0.7)band1Q = 0.7;
	else if (band1Q > 5)band1Q = 5;
	updateBand1();
}

void setBand2Q(float q) {
	band2Q += q * 0.3;
	if (band2Q < 0.7)band2Q = 0.7;
	else if (band2Q > 5)band2Q = 5;
	updateBand2();
}

void setHighShelfQ(float q) {
	highShelfQ += q * 0.3;
	updateHighShelf();
}
