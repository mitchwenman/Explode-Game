#ifndef PIXELDRAWER_
#define PIXELDRAWER_

#include "RGBColor.h"

class PixelDrawer
{

public:
	static int numColourChannels, frameWidth;
	static BYTE* frameBuffer;

	/******************
	Description: Draws a pixel to the buffer.
	Parameters: int x, y: The projected x and y values onto the 2d screen
				BYTE r, g, b			  : The rgb values.
	Preconditions: Input param is not null.
	Postconditions: NIL
	Returns: void
	*******************///
	static void setPixel(int x, int y, BYTE r, BYTE g, BYTE b);

	/******************
	Description: Draws a pixel to the screen, first checking the zbuffer.
	Parameters: int projectedX, projectedY: The projected x and y values onto the 2d screen
				int z					  : The z coordinate (original)
				BYTE r, g, b			  : The rgb values.
	Preconditions: NIL
	Postconditions: NIL
	Returns: void
	*******************///
	static void set3DProjectedPixel(int projectedX, int projectedY, int z, BYTE r, BYTE g, BYTE b);

	/******************
	Description: Draws a pixel to the screen.
	Parameters: int x, y: The projected x and y values onto the 2d screen
				BYTE r, g, b			  : The rgb values.
				BYTE* frameBuffer		  : The frame buffer
				int numColourChannels	  : The number of colour channels
				int frameWidth			  : The width of the window frame.
	Preconditions: NIL
	Postconditions: NIL
	Returns: void
	*******************///
	static void setPixel(int x, int y, BYTE r, BYTE g, BYTE b, BYTE* frameBuffer, int numColourChannels, int frameWidth);
};

#endif