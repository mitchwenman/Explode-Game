#include "PixelDrawer.h"
#include "DDALine.h"
#include "GraphicsUtil.h"

namespace LineDrawer
{
	void drawLine(DDALine* line, RGBColour* colour1, RGBColour* colour2);

	void drawLine(int x1, int y1, int x2, int y2, RGBColour* colour1, RGBColour* colour2);
	 
}