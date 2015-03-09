#include "LineDrawer.h"


namespace LineDrawer
{
	void drawLine(DDALine* line, RGBColour* colour1, RGBColour* colour2)
	{
		
		//Create x,y double vars for better rounding
		double x = line->x1;
		double y = line->y1;
		//Calculate colour diffs
		double r, g, b, rdiff, gdiff, bdiff;
		r = (double)colour1->red; g = (double)colour1->green; b = (double)colour1->blue;
		rdiff = (colour2->red - colour1->red)/line->steps;
		gdiff = (colour2->green - colour1->green)/line->steps;
		bdiff = (colour2->blue - colour1->blue)/line->steps;
		//Draw the line
		for (int i = 0; i < line->steps; i++)
		{
			PixelDrawer::setPixel(ROUND(x), ROUND(y), (int)r, (int)g, (int)b);
			x += line->xInc;
			y += line->yInc;
			r += rdiff; 
			g += gdiff;
			b += bdiff;
		}
	}

	void drawLine(int x1, int y1, int x2, int y2, RGBColour* colour1, RGBColour* colour2)
	{
		DDALine* line = new DDALine(x1, y1, x2, y2);
		drawLine(line, colour1, colour2);
		delete(line);
	}
	 
}