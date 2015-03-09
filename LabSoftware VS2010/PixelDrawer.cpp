#include "PixelDrawer.h"

int PixelDrawer::frameWidth;
int PixelDrawer::numColourChannels = 3;
BYTE* PixelDrawer::frameBuffer;

void PixelDrawer::setPixel(int x, int y, BYTE r, BYTE g, BYTE b)
{
	PixelDrawer::setPixel(x, y, r, g, b, PixelDrawer::frameBuffer, numColourChannels, frameWidth);
}

void PixelDrawer::setPixel(int x, int y, BYTE r, BYTE g, BYTE b, BYTE* frameBuffer, int numColourChannels, int frameWidth)
{
	BYTE* screen = (BYTE*)frameBuffer; 

	//Set red, green and blue
	screen[numColourChannels * (x + y * frameWidth) + RED_OFFSET] = r;
	screen[numColourChannels * (x + y * frameWidth) + GREEN_OFFSET] = g;
	screen[numColourChannels * (x + y * frameWidth) + BLUE_OFFSET] = b;
}

