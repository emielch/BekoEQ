#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder enc1(4, 5);
Encoder enc2(1, 2);
//   avoid using pins with LEDs attached

long enc1Pos = 0;
long enc2Pos = 0;

Color leftCol = Color(0, 100, 100, HSB_MODE);
Color rightCol = Color(120, 100, 100, HSB_MODE);

void updateEncoders() {
	long enc1NewPos = enc1.read();
	long enc2NewPos = enc2.read();

	if (enc1NewPos / 4 != enc1Pos / 4) {
		long delta = enc1NewPos/4 - enc1Pos/4;
		if (delta>0) gui.inputLeft(delta);
		else gui.inputRight(-delta);
		enc1Pos = enc1NewPos;

		leftCol.setHSB(leftCol.hue() + delta*5, leftCol.saturation(), leftCol.brightness());
		strip.setPixelColor(0, leftCol.red(), leftCol.green(), leftCol.blue());
		//strip.show();
	}

	if (enc2NewPos / 4 != enc2Pos / 4) {
		long delta = enc2NewPos / 4 - enc2Pos / 4;
		if (delta>0) gui.inputDown(delta);
		else gui.inputUp(-delta);
		enc2Pos = enc2NewPos;

		rightCol.setHSB(rightCol.hue() + delta*5, rightCol.saturation(), rightCol.brightness());
		strip.setPixelColor(1, rightCol.red(), rightCol.green(), rightCol.blue());
		//strip.show();
	}
}


void updateButtons() {
	if (button1.update()) {
		if (button1.risingEdge()) {
			gui.inputRight(1);
		}
	}

	if (button2.update()) {
		if (button2.risingEdge()) {
			gui.inputLeft(1);
		}
	}
}


