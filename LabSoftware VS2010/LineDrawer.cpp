///////////////////////////////////////////////////////////////////////////////////
// Filename: LineDrawer.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Functions for drawing a 2D line to the screen.
///////////////////////////////////////////////////////////////////////////////////

//=======INCLUDES=========//
#include "LineDrawer.h"
#include "DDALine.h"
#include "GraphicsSettings.h"
#ifdef _WIN32
	#include <windows.h>
#endif

#include <stdlib.h>
#include <math.h>


//=========FUNCTIONS========//

namespace LineDrawer
{
	void drawLine(GPLine* gpLine)
	{
		DDALine* line = calculateAndClipLine(gpLine);	
		if (line != NULL)
		{
			RGBColour colour1 = line->c1;
			RGBColour colour2 = line->c2;
			//Create x,y double vars for better rounding
			double x = line->x1;
			double y = line->y1;
			double z = line->z1;
			//Calculate colour diffs
			double r, g, b, rdiff, gdiff, bdiff;
			r = (double)colour1.red; g = (double)colour1.green; b = (double)colour1.blue;
			rdiff = (colour2.red - colour1.red)/line->steps;
			gdiff = (colour2.green - colour1.green)/line->steps;
			bdiff = (colour2.blue - colour1.blue)/line->steps;
			//Draw the line
			for (int i = 0; i < line->steps; i++)
			{
				PixelDrawer::set3DProjectedPixel(ceil(x), ceil(y - 0.5), z, (int)r, (int)g, (int)b);
				x += line->xInc;
				y += line->yInc;
				z += line->zInc;
				r += rdiff; 
				g += gdiff;
				b += bdiff;
			}
			delete(line);
		}
				
	}

	DDALine* calculateAndClipLine(GPLine* gpLine)
	{
		GraphicsSettings* gSettings = GraphicsSettings::getGraphicsSettings();
		int view = gSettings->getView();
		gpLine->x1 += view; 
		gpLine->x2 += view;
		DDALine* line;
		if (lineNeedsClipping(gpLine))
		{
			GPLine* clippedLine = clipLine(gpLine);
			if (clippedLine == NULL) 
				return NULL; //Line is outside frame, don't draw anything
			line = new DDALine(clippedLine);
			delete(clippedLine);
		} else
		{
			line = new DDALine(gpLine);
		}
		return line;
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
		int x0, y0, z0, x1, y1, z1;
		x0 = min(line->x1, line->x2);
		if (x0 == line->x1)
		{
			y0 = line->y1;
			z0 = line->z1;
			x1 = line->x2;
			y1 = line->y2;
			z1 = line->z2;
		} else
		{
			y0 = line->y2;
			z0 = line->z2;
			x1 = line->x1;
			y1 = line->y1;
			z1 = line->z1;
		}

		double t0 = 0;
		double t1 = 1;
		int deltaX = x1 - x0;
		int deltaY = y1 - y0;
		int deltaZ = z1 - z0;
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

		int newx1 = (x0 + t0 * deltaX);
		int newy1 = (y0 + t0 * deltaY);		 
		int newx2 = x0 + t1 * deltaX;
		int newy2 = y0 + t1 * deltaY;

		int newz1, newz2;
		if (int(t0) == 1) 
			newz1 = z0;
		else
			newz1 = z0 + t0 * deltaZ;
		if (int(t1) == 1)
			newz2 = z1;
		else 
			newz2 = z0 + t1 * deltaZ;

		
		VERTEX_3D p1_3d = { newx1, newy1, newz1, line->c1 };
		VERTEX_3D p2_3d = { newx2, newy2, newz2, line->c2 };
 		if (x0 == line->x1 && y0 == line->y1)
		{			
			return new GPLine(p1_3d, p2_3d);
		}
		else
		{			
			return new GPLine(p2_3d, p1_3d);
		}
	}

	bool lineNeedsClipping(GPLine* line)
	{
		GraphicsSettings* settings = GraphicsSettings::getGraphicsSettings();
		int minX = 0; int maxX = settings->getFrameWidth() - 1;
		int minY = 0; int maxY = settings->getFrameHeight() - 1;
		if (line->x1 < minX || line->x1 > maxX) return true;
		if (line->x2 < minX || line->x2 > maxX) return true;
		if (line->y1 < minY || line->y1 > maxY) return true;
		if (line->y2 < minY || line->y2 > maxY) return true;
		
		//All conditions failed - line doesn't need clipping
		return false;
	}
	 
}