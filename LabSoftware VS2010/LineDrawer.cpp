#include "LineDrawer.h"
#include "DDALine.h"
#include <stdlib.h>

namespace LineDrawer
{
	void drawLine(GPLine* gpLine, RGBColour* colour1, RGBColour* colour2)
	{
		GPLine* clippedLine = clipLine(gpLine);
		DDALine* line = new DDALine(clippedLine);
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
		GPLine* line = new GPLine(x1, y1, x2, y2);
		drawLine(line, colour1, colour2);
		delete(line);
	}

	void drawLine(int x1, int y1, int x2, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2)
	{
		RGBColour* c1 = (RGBColour*)malloc(sizeof(RGBColour));
		RGBColour* c2 = (RGBColour*)malloc(sizeof(RGBColour));
		c1->red = r1; c1->green = g1; c1->blue = b1;
		c2->red = r2; c2->green = g2; c2->blue = b2;
		drawLine(x1, y1, x2, y2, c1, c2);
		//clean up
		free(c1);
		free(c2);
	}

	GPLine* clipLine(GPLine* line)
	{
		return new GPLine(line->x1, line->y1, line->x2, line->y2);
	}
	 
}