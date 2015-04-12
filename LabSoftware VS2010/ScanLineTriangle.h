#ifndef SCANLINETRIANGLE_
#define SCANLINETRIANGLE_

#include "RGBColor.h"

class ScanLineTriangle
{

public:
	int XTopVert, YTopVert, ZTopVert, 
		XLeftVert, YLeftVert, ZLeftVert,
		XRightVert, YRightVert, ZRightVert;
	int hRight, hLeft;
	RGBColour colourTop, colourLeft, colourRight; 

	//Creates a scan line triangle representation given 3 vertices 
	ScanLineTriangle(int x1, int y1, int z1, int x2, int y2, int z2,
					int x3, int y3, int z3, 
					RGBColour colour1, RGBColour colour2, RGBColour colour3);

	
};

#endif