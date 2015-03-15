#ifndef GPLINE_
#define GPLINE_

#include "RGBColor.h"
#include "GraphicsUtil.h"

class GPLine
{
	
public:
	int x1, y1, x2, y2;
	RGBColour *c1, *c2;
		
	GPLine(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};

	GPLine(VERTEX p1, VERTEX p2) : x1(p1.x), y1(p1.y), x2(p2.x), y2(p2.y), c1(p1.c), c2(p2.c) {};
};

#endif