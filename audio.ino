#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputUSB            usb_in;         //xy=695.6110229492188,904.7499389648438
AudioInputI2S            i2s1;           //xy=704.7222290039062,499.6388854980469
AudioAnalyzeRMS          rms1;           //xy=830.9444580078125,604.0833129882812
AudioSynthWaveformDc     usb_inputMult; //xy=881.333251953125,908.2222290039062
AudioOutputUSB           usb_out;        //xy=896.1666259765625,499.63885498046875
AudioSynthWaveformDc     jack_inputMult;      //xy=944.2777099609375,545.3054809570312
AudioEffectMultiply      usb_mult_R; //xy=1031.3333740234375,999.3333129882812
AudioEffectMultiply      usb_mult_L; //xy=1033.3333435058594,843.3333129882812
AudioEffectMultiply      jack_mult_R;      //xy=1038.5,622.75
AudioEffectMultiply      jack_mult_L;      //xy=1046.5,468.75
AudioFilterBiquad        biquad_usb_L; //xy=1188.3333435058594,843.3333129882812
AudioFilterBiquad        biquad_usb_R; //xy=1188.3333740234375,999.3333129882812
AudioFilterBiquad        biquad_jack_R;        //xy=1202.5,623.75
AudioFilterBiquad        biquad_jack_L;        //xy=1214.5,467.75
AudioFilterStateVariable band1_usb_R; //xy=1392.8887329101562,1022.0000610351562
AudioFilterStateVariable band2_usb_R; //xy=1394.8887329101562,1074.0000610351562
AudioFilterStateVariable band1_usb_L; //xy=1395.888916015625,871.111083984375
AudioFilterStateVariable band2_usb_L; //xy=1396.888916015625,929.111083984375
AudioFilterStateVariable band1_jack_R;        //xy=1419.0555419921875,656.4166870117188
AudioFilterStateVariable band1_jack_L;        //xy=1419.8333740234375,501.08331298828125
AudioFilterStateVariable band2_jack_L;        //xy=1420.8333740234375,559.0833129882812
AudioFilterStateVariable band2_jack_R;        //xy=1421.0555419921875,708.4166870117188
AudioMixer4              mixer3; //xy=1613.22216796875,837.2223510742188
AudioMixer4              mixer4; //xy=1616.22216796875,996.2223510742188
AudioMixer4              filterBugFixer_2; //xy=1616.6666259765625,918.8890380859375
AudioMixer4              mixer1;         //xy=1794.0555419921875,490.19439697265625
AudioMixer4              mixer2;         //xy=1797.0555419921875,649.1943969726562
AudioMixer4              filterBugFixer_1;         //xy=1797.5,571.861083984375
AudioOutputI2S           i2s2;           //xy=1992.0555419921875,556.1943969726562
AudioAnalyzePeak         peakOut_left;   //xy=1997.0555419921875,479.19439697265625
AudioAnalyzePeak         peakOut_right;  //xy=2000.0555419921875,651.1943969726562
AudioConnection          patchCord1(usb_in, 0, usb_mult_L, 0);
AudioConnection          patchCord2(usb_in, 1, usb_mult_R, 0);
AudioConnection          patchCord3(i2s1, 0, usb_out, 0);
AudioConnection          patchCord4(i2s1, 0, jack_mult_L, 0);
AudioConnection          patchCord5(i2s1, 1, usb_out, 1);
AudioConnection          patchCord6(i2s1, 1, rms1, 0);
AudioConnection          patchCord7(i2s1, 1, jack_mult_R, 0);
AudioConnection          patchCord8(usb_inputMult, 0, usb_mult_L, 1);
AudioConnection          patchCord9(usb_inputMult, 0, usb_mult_R, 1);
AudioConnection          patchCord10(jack_inputMult, 0, jack_mult_L, 1);
AudioConnection          patchCord11(jack_inputMult, 0, jack_mult_R, 1);
AudioConnection          patchCord12(usb_mult_R, biquad_usb_R);
AudioConnection          patchCord13(usb_mult_L, biquad_usb_L);
AudioConnection          patchCord14(jack_mult_R, biquad_jack_R);
AudioConnection          patchCord15(jack_mult_L, biquad_jack_L);
AudioConnection          patchCord16(biquad_usb_L, 0, band1_usb_L, 0);
AudioConnection          patchCord17(biquad_usb_L, 0, band2_usb_L, 0);
AudioConnection          patchCord18(biquad_usb_L, 0, mixer3, 0);
AudioConnection          patchCord19(biquad_usb_R, 0, band1_usb_R, 0);
AudioConnection          patchCord20(biquad_usb_R, 0, band2_usb_R, 0);
AudioConnection          patchCord21(biquad_usb_R, 0, mixer4, 0);
AudioConnection          patchCord22(biquad_jack_R, 0, mixer2, 0);
AudioConnection          patchCord23(biquad_jack_R, 0, band1_jack_R, 0);
AudioConnection          patchCord24(biquad_jack_R, 0, band2_jack_R, 0);
AudioConnection          patchCord25(biquad_jack_L, 0, band1_jack_L, 0);
AudioConnection          patchCord26(biquad_jack_L, 0, band2_jack_L, 0);
AudioConnection          patchCord27(biquad_jack_L, 0, mixer1, 0);
AudioConnection          patchCord28(band1_usb_R, 0, filterBugFixer_2, 2);
AudioConnection          patchCord29(band1_usb_R, 1, mixer4, 1);
AudioConnection          patchCord30(band2_usb_R, 0, filterBugFixer_2, 3);
AudioConnection          patchCord31(band2_usb_R, 1, mixer4, 2);
AudioConnection          patchCord32(band1_usb_L, 0, filterBugFixer_2, 0);
AudioConnection          patchCord33(band1_usb_L, 1, mixer3, 1);
AudioConnection          patchCord34(band2_usb_L, 0, filterBugFixer_2, 1);
AudioConnection          patchCord35(band2_usb_L, 1, mixer3, 2);
AudioConnection          patchCord36(band1_jack_R, 0, filterBugFixer_1, 2);
AudioConnection          patchCord37(band1_jack_R, 1, mixer2, 1);
AudioConnection          patchCord38(band1_jack_L, 0, filterBugFixer_1, 0);
AudioConnection          patchCord39(band1_jack_L, 1, mixer1, 1);
AudioConnection          patchCord40(band2_jack_L, 0, filterBugFixer_1, 1);
AudioConnection          patchCord41(band2_jack_L, 1, mixer1, 2);
AudioConnection          patchCord42(band2_jack_R, 0, filterBugFixer_1, 3);
AudioConnection          patchCord43(band2_jack_R, 1, mixer2, 2);
AudioConnection          patchCord44(mixer3, 0, mixer1, 3);
AudioConnection          patchCord45(mixer4, 0, mixer2, 3);
AudioConnection          patchCord46(mixer1, 0, i2s2, 0);
AudioConnection          patchCord47(mixer1, peakOut_left);
AudioConnection          patchCord48(mixer2, 0, i2s2, 1);
AudioConnection          patchCord49(mixer2, peakOut_right);
AudioControlSGTL5000     sgtl5000_1;     //xy=1165.4999389648438,205.41665649414062
// GUItool: end automatically generated code



float inputMult = 0.4;

EQ_SETTINGS current_EQ_settings = { 0,200,1,0,500,0.7,0,2000,0.7,0,7000,1 };
EQ_SETTINGS current_jack_EQ_settings = { 0,200,1,0,500,0.7,0,2000,0.7,0,7000,1 };
EQ_SETTINGS current_usb_EQ_settings = { 0,200,1,0,500,0.7,0,2000,0.7,0,7000,1 };

unsigned long lastNoiseThresh = 0;

float jackIn_gain = 1;
float USBIn_gain = 1;

float peakOutLeftVal = 0;
float peakOutRightVal = 0;


void setupAudio() {
	AudioMemory(120);
	jack_inputMult.amplitude(jackIn_gain*inputMult);  // usb input amp is set in updateAudio() loop

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
		jack_inputMult.amplitude(jackIn_gain*inputMult);
	}
	else if (!jackInOn && jackIn_gain > 0.0) {
		jackIn_gain -= 0.01*dt;
		jack_inputMult.amplitude(jackIn_gain*inputMult);
	}

	float usb_vol = usb_in.volume()*10;
	if (USBInOn && USBIn_gain < 1.0) {
		USBIn_gain += 0.01*dt;
	}
	else if (!USBInOn && USBIn_gain > 0.0) {
		USBIn_gain -= 0.01*dt;
	}
	usb_inputMult.amplitude(USBIn_gain*usb_vol*inputMult);
}

void updateLowShelf() {
	biquad_jack_L.setLowShelf(0, current_EQ_settings.lowShelfFreq, current_EQ_settings.lowShelfGain, current_EQ_settings.lowShelfQ);
	biquad_jack_R.setLowShelf(0, current_EQ_settings.lowShelfFreq, current_EQ_settings.lowShelfGain, current_EQ_settings.lowShelfQ);

	biquad_usb_L.setLowShelf(0, current_EQ_settings.lowShelfFreq, current_EQ_settings.lowShelfGain, current_EQ_settings.lowShelfQ);
	biquad_usb_R.setLowShelf(0, current_EQ_settings.lowShelfFreq, current_EQ_settings.lowShelfGain, current_EQ_settings.lowShelfQ);

	scheduleEQSave();
}

void updateBand1() {
	band1_jack_L.frequency(current_EQ_settings.band1Freq);
	band1_jack_L.resonance(current_EQ_settings.band1Q);
	mixer1.gain(1, current_EQ_settings.band1Gain);

	band1_jack_R.frequency(current_EQ_settings.band1Freq);
	band1_jack_R.resonance(current_EQ_settings.band1Q);
	mixer2.gain(1, current_EQ_settings.band1Gain);


	band1_usb_L.frequency(current_EQ_settings.band1Freq);
	band1_usb_L.resonance(current_EQ_settings.band1Q);
	mixer3.gain(1, current_EQ_settings.band1Gain);

	band1_usb_R.frequency(current_EQ_settings.band1Freq);
	band1_usb_R.resonance(current_EQ_settings.band1Q);
	mixer4.gain(1, current_EQ_settings.band1Gain);

	scheduleEQSave();

	/*biquad1.setNotch(2, band1Freq, band1Q);
	  biquad2.setNotch(2, band1Freq, band1Q);*/
}

void updateBand2() {
	band2_jack_L.frequency(current_EQ_settings.band2Freq);
	band2_jack_L.resonance(current_EQ_settings.band2Q);
	mixer1.gain(2, current_EQ_settings.band2Gain);

	band2_jack_R.frequency(current_EQ_settings.band2Freq);
	band2_jack_R.resonance(current_EQ_settings.band2Q);
	mixer2.gain(2, current_EQ_settings.band2Gain);


	band2_usb_L.frequency(current_EQ_settings.band2Freq);
	band2_usb_L.resonance(current_EQ_settings.band2Q);
	mixer3.gain(2, current_EQ_settings.band2Gain);

	band2_usb_R.frequency(current_EQ_settings.band2Freq);
	band2_usb_R.resonance(current_EQ_settings.band2Q);
	mixer4.gain(2, current_EQ_settings.band2Gain);

	scheduleEQSave();

	/*biquad1.setNotch(3, band2Freq, band2Q);
	  biquad2.setNotch(3, band2Freq, band2Q);*/
}

void updateHighShelf() {
	biquad_jack_L.setHighShelf(1, current_EQ_settings.highShelfFreq, current_EQ_settings.highShelfGain, current_EQ_settings.highShelfQ);
	biquad_jack_R.setHighShelf(1, current_EQ_settings.highShelfFreq, current_EQ_settings.highShelfGain, current_EQ_settings.highShelfQ);

	biquad_usb_L.setHighShelf(1, current_EQ_settings.highShelfFreq, current_EQ_settings.highShelfGain, current_EQ_settings.highShelfQ);
	biquad_usb_R.setHighShelf(1, current_EQ_settings.highShelfFreq, current_EQ_settings.highShelfGain, current_EQ_settings.highShelfQ);
	scheduleEQSave();
}


// FREQ
void setLowShelfFreq(float freq, void* page) {
	current_EQ_settings.lowShelfFreq += current_EQ_settings.lowShelfFreq * 0.03 * freq;
	if (current_EQ_settings.lowShelfFreq < 0.1)current_EQ_settings.lowShelfFreq = 0.1;
	else if (current_EQ_settings.lowShelfFreq > 22050)current_EQ_settings.lowShelfFreq = 22050;
	updateLowShelf();
}

void setBand1Freq(float freq, void* page) {
	current_EQ_settings.band1Freq += current_EQ_settings.band1Freq * 0.03 * freq;;
	if (current_EQ_settings.band1Freq < 0.1)current_EQ_settings.band1Freq = 0.1;
	else if (current_EQ_settings.band1Freq > 22050)current_EQ_settings.band1Freq = 22050;
	updateBand1();
}

void setBand2Freq(float freq, void* page) {
	current_EQ_settings.band2Freq += current_EQ_settings.band2Freq * 0.03 * freq;;
	if (current_EQ_settings.band2Freq < 0.1)current_EQ_settings.band2Freq = 0.1;
	else if (current_EQ_settings.band2Freq > 22050)current_EQ_settings.band2Freq = 22050;
	updateBand2();
}

void setHighShelfFreq(float freq, void* page) {
	current_EQ_settings.highShelfFreq += current_EQ_settings.highShelfFreq * 0.03 * freq;;
	if (current_EQ_settings.highShelfFreq < 0.1)current_EQ_settings.highShelfFreq = 0.1;
	else if (current_EQ_settings.highShelfFreq > 22050)current_EQ_settings.highShelfFreq = 22050;
	updateHighShelf();
}

// GAIN
void setLowShelfGain(float gain, void* page) {
	current_EQ_settings.lowShelfGain += gain * 0.3;
	updateLowShelf();
}

void setBand1Gain(float gain, void* page) {
	current_EQ_settings.band1Gain += gain * 0.3;
	if (current_EQ_settings.band1Gain < 0)current_EQ_settings.band1Gain = 0;
	else if (current_EQ_settings.band1Gain > 20)current_EQ_settings.band1Gain = 20;
	updateBand1();
}

void setBand2Gain(float gain, void* page) {
	current_EQ_settings.band2Gain += gain * 0.3;
	if (current_EQ_settings.band2Gain < 0)current_EQ_settings.band2Gain = 0;
	else if (current_EQ_settings.band2Gain > 20)current_EQ_settings.band2Gain = 20;
	updateBand2();
}

void setHighShelfGain(float gain, void* page) {
	current_EQ_settings.highShelfGain += gain * 0.3;
	updateHighShelf();
}


// Q
void setLowShelfQ(float q, void* page) {
	current_EQ_settings.lowShelfQ += q * 0.3;
	updateLowShelf();
}

void setBand1Q(float q, void* page) {
	current_EQ_settings.band1Q += q * 0.3;
	if (current_EQ_settings.band1Q < 0.7)current_EQ_settings.band1Q = 0.7;
	else if (current_EQ_settings.band1Q > 5)current_EQ_settings.band1Q = 5;
	updateBand1();
}

void setBand2Q(float q, void* page) {
	current_EQ_settings.band2Q += q * 0.3;
	if (current_EQ_settings.band2Q < 0.7)current_EQ_settings.band2Q = 0.7;
	else if (current_EQ_settings.band2Q > 5)current_EQ_settings.band2Q = 5;
	updateBand2();
}

void setHighShelfQ(float q, void* page) {
	current_EQ_settings.highShelfQ += q * 0.3;
	updateHighShelf();
}
