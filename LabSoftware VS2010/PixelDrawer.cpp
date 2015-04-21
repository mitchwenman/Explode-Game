///////////////////////////////////////////////////////////////////////////////////
// Filename: PixelDrawer.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Functions for drawing a pixel to the display.
///////////////////////////////////////////////////////////////////////////////////

#include "PixelDrawer.h"
#include "GraphicsSettings.h"
#include "ZBuffer.h"

int PixelDrawer::frameWidth;
int PixelDrawer::numColourChannels = 3;
BYTE* PixelDrawer::frameBuffer;

void PixelDrawer::setPixel(int x, int y, BYTE r, BYTE g, BYTE b)
{
	GraphicsSettings* settings = GraphicsSettings::getGraphicsSettings();
	PixelDrawer::setPixel(x, y, r, g, b, settings->getFrameBuffer(), 
		settings->getNumberOfChannels(), settings->getFrameWidth());
}

void PixelDrawer::set3DProjectedPixel(int projectedX, int projectedY, int z, BYTE r, BYTE g, BYTE b)
{
	ZBuffer* zbuffer = ZBuffer::getSingleton();
	if (zbuffer->shouldDrawPixel(projectedX, projectedY, z))
		setPixel(projectedX, projectedY, r, g, b);
}

void PixelDrawer::setPixel(int x, int y, BYTE r, BYTE g, BYTE b, BYTE* frameBuffer, int numColourChannels, int frameWidth)
{
	BYTE* screen = (BYTE*)frameBuffer; 

	//Set red, green and blue
	screen[numColourChannels * (x + y * frameWidth) + RED_OFFSET] = r;
	screen[numColourChannels * (x + y * frameWidth) + GREEN_OFFSET] = g;
	screen[numColourChannels * (x + y * frameWidth) + BLUE_OFFSET] = b;
}

