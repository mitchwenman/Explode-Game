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

	/******************
	Description:Constructor for a scan line triangle
	Parameters: int x1, x2, x3: THe x values of the points.
				int y1, y2, y3: The y values of the points.
				RGBColour colour1, colour2. colour3: The colours at each vertex
	Preconditions: Input param(s) not null.
	Postconditions: NIL
	Returns:  
	*******************/ 
	ScanLineTriangle(int x1, int y1, int z1, int x2, int y2, int z2,
					int x3, int y3, int z3, 
					RGBColour colour1, RGBColour colour2, RGBColour colour3);

	
};

#endif