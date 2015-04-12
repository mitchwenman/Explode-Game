#ifndef GPLINE_
#define GPLINE_

#include "RGBColor.h"
#include "GraphicsUtil.h"

class GPLine
{
	
public:
	int x1, y1, x2, y2, z1, z2;
	RGBColour c1, c2;
	
	//Creates a GPLine given a 2 points
	GPLine(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};

	//Creates a GPLine from two vertices
	GPLine(VERTEX_3D p1, VERTEX_3D p2) : x1(p1.x), y1(p1.y), z1(p1.z), x2(p2.x), y2(p2.y), z2(p2.z), c1(p1.c), c2(p2.c) {};
};

#endif