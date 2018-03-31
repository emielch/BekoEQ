// 
// 
// 

#include "Drawable.h"


Drawable::Drawable()
{
	updateDrawing = true;
}

void Drawable::update() {

}

void Drawable::resetDrawing() {
	updateDrawing = true;
}

void Drawable::draw(ILI9341_t3 tft, boolean force) {
	if (force) updateDrawing = true;
	draw(tft);
}

void Drawable::draw(ILI9341_t3 tft) {
	if (!updateDrawing) return;
}