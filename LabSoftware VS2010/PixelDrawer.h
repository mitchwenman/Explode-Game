#ifndef PIXELDRAWER_
#define PIXELDRAWER_

#include "RGBColor.h"

class PixelDrawer
{

public:
	static int numColourChannels, frameWidth;
	static BYTE* frameBuffer;

	//Puts a pixel in the frame buffer
	static void setPixel(int x, int y, BYTE r, BYTE g, BYTE b);

	//Puts a pixel in the given frame buffer, with a number of colour channels and a framewidth
	static void setPixel(int x, int y, BYTE r, BYTE g, BYTE b, BYTE* frameBuffer, int numColourChannels, int frameWidth);
};

#endif