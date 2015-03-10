#include "PixelDrawer.h"
#include "GPLine.h"
#include "GraphicsUtil.h"

namespace LineDrawer
{
	void drawLine(GPLine* gpLine, RGBColour* colour1, RGBColour* colour2);

	void drawLine(int x1, int y1, int x2, int y2, RGBColour* colour1, RGBColour* colour2);

	void drawLine(int x1, int x2, int y1, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2);

	GPLine* clipLine(GPLine* line);
	 
}