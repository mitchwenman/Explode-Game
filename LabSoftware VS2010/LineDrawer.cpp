#include "LineDrawer.h"
#include "DDALine.h"
#include "GraphicsSettings.h"
#ifdef _WIN32
	#include <windows.h>
#endif

#include <stdlib.h>
#include <math.h>

namespace LineDrawer
{
	void drawLine(GPLine* gpLine)
	{
		DDALine* line;
		if (lineNeedsClipping(gpLine))
		{
			GPLine* clippedLine = clipLine(gpLine);
			if (clippedLine == NULL) 
				return; //Line is outside frame, don't draw anything
			line = new DDALine(clippedLine);
			delete(clippedLine);
		} else
		{
			line = new DDALine(gpLine);
		}	
		RGBColour* colour1 = line->c1;
		RGBColour* colour2 = line->c2;
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
			PixelDrawer::setPixel(ceil(x), ceil(y - 1), (int)r, (int)g, (int)b);
			x += line->xInc;
			y += line->yInc;
			r += rdiff; 
			g += gdiff;
			b += bdiff;
		}
		delete(line);
		
		
		
	}

	void drawLine(int x1, int y1, int x2, int y2, RGBColour* colour1, RGBColour* colour2)
	{
		GPLine* line = new GPLine(x1, y1, x2, y2);
		line->c1 = colour1; line->c2 = colour2;
		drawLine(line);
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
		//Get edge details
		GraphicsSettings* settings = GraphicsSettings::getGraphicsSettings();
		int leftEdge = 0;
		int topEdge = settings->getFrameHeight() - 1;
		int rightEdge = settings->getFrameWidth() - 1;
		int bottomEdge = 0;

		//Vars for calculation
		int x0, y0, x1, y1;
		x0 = min(line->x1, line->x2);
		if (x0 == line->x1)
		{
			y0 = line->y1;
			x1 = line->x2;
			y1 = line->y2;
		} else
		{
			y0 = line->y2;
			x1 = line->x1;
			y1 = line->y1;
		}

		double t0 = 0;
		double t1 = 1;
		int deltaX = x1 - x0;
		int deltaY = y1 - y0;
		double p, q, r;
		enum Edges { LEFT, TOP, RIGHT, BOTTOM }; //For readability in loop
		for (int edge = LEFT; edge <= BOTTOM; edge++)
		{
			if (edge == LEFT) {		p = -deltaX;	q = -(leftEdge - x0); }
			if (edge == TOP) {		p = deltaY;		q = topEdge - y0; }
			if (edge == RIGHT) {	p = deltaX;		q = rightEdge - x0; }	 
			if (edge == BOTTOM) {	p = -deltaY;	q = -(bottomEdge - y0); }
			r = q/p;

			if (p < 0)
			{
				if (r > t1) return NULL;
				else if (r > t0) t0 = r;
			} else if (p > 0)
			{
				if ( r < t0) return NULL;
				else if (r < t1) t1 = r;
			} else if (q < 0)
				return NULL;
			
		}
		VERTEX p1 = { (int)(x0 + t0 * deltaX), (int)(y0 + t0 * deltaY), line->c1 };
		VERTEX p2 = { (int)(x0 + t1 * deltaX), (int)(y0 + t1 * deltaY), line->c2 };

 		if (x0 == line->x1 && y0 == line->y1)
			return new GPLine(p1, p2);
		else
			return new GPLine(p2, p1);
	}

	bool lineNeedsClipping(GPLine* line)
	{
		GraphicsSettings* settings = GraphicsSettings::getGraphicsSettings();
		int minX = 0; int maxX = settings->getFrameWidth();
		int minY = 0; int maxY = settings->getFrameHeight();
		if (line->x1 < minX || line->x1 > maxX) return true;
		if (line->x2 < minX || line->x2 > maxX) return true;
		if (line->y1 < minY || line->y1 > maxY) return true;
		if (line->y2 < minY || line->y2 > maxY) return true;
		
		//All conditions failed - line doesn't need clipping
		return false;
	}
	 
}