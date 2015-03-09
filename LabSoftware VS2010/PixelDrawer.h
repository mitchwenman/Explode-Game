#ifndef PIXELDRAWER_
#define PIXELDRAWER_

#include "RGBColor.h"

class PixelDrawer
{

public:
	static int numColourChannels, frameWidth;
	static BYTE* frameBuffer;

	static void setPixel(int x, int y, BYTE r, BYTE g, BYTE b);
	static void setPixel(int x, int y, BYTE r, BYTE g, BYTE b, BYTE* frameBuffer, int numColourChannels, int frameWidth);
};

#endif