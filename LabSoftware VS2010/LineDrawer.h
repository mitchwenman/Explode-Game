#include "PixelDrawer.h"
#include "GPLine.h"
#include "GraphicsUtil.h"
#include "DDALine.h"

namespace LineDrawer
{
	//Draws a line by calculating a DDALine
	void drawLine(GPLine* gpLine);

	//Clips a line and calculates the DDA values for it
	DDALine* calculateAndClipLine(GPLine* gpLine);

	//Draws a line between 2 points given RGB colour values
	void drawLine(int x1, int y1, int x2, int y2, RGBColour colour1, RGBColour colour2);

	//Draws a line between 2 points given BYTE values for colours
	void drawLine(int x1, int y1, int x2, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2);

	//Clips a line using Liang-Barsky line clipping
	GPLine* clipLine(GPLine* line);

	//Checks if a line requires clipping
	bool lineNeedsClipping(GPLine* line);
	 
}