#ifndef EQ_STRUCTS
#define EQ_STRUCTS


struct EQ_SETTINGS {
	float lowShelfGain;
	float lowShelfFreq;
	float lowShelfQ;

	float band1Gain;
	float band1Freq;
	float band1Q;

	float band2Gain;
	float band2Freq;
	float band2Q;

	float highShelfGain;
	float highShelfFreq;
	float highShelfQ;
};


#endif