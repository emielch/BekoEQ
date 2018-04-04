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

void updateEncoders() {
	long enc1NewPos = enc1.read();
	long enc2NewPos = enc2.read();

	if (enc1NewPos / 4 != enc1Pos / 4) {
		long delta = enc1NewPos/4 - enc1Pos/4;
		if (delta>0) gui.inputLeft(delta);
		else gui.inputRight(-delta);
		enc1Pos = enc1NewPos;
	}

	if (enc2NewPos / 4 != enc2Pos / 4) {
		long delta = enc2NewPos / 4 - enc2Pos / 4;
		if (delta>0) gui.inputDown(delta);
		else gui.inputUp(-delta);
		enc2Pos = enc2NewPos;
	}
}

bool button1pressed = false;
bool button2pressed = false;
void button1isr() {
	button1pressed = true;
}
void button2isr() {
	button2pressed = true;
}

void updateButtons() {
	if (button1pressed) {
		gui.inputRight(1);
		button1pressed = false;
	}
	if (button2pressed) {
		gui.inputLeft(1);
		button2pressed = false;
	}
}


