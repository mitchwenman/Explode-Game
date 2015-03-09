#ifdef _WIN32
	#include <windows.h>
#endif

#include <math.h>
#include "ScanLineTriangle.h"



ScanLineTriangle::ScanLineTriangle(int x1, int y1, int x2, int y2, int x3, int y3, 
						RGBColour* colour1, RGBColour* colour2, RGBColour* colour3)
{
	int X0, X1, X2, Y0, Y1, Y2; //For holding vertices after (highest) is found
	RGBColour *c0, *c2; 
	int max = max(max(y1, y2), y3);
	//Reassign to vars for rest of alg to work
	//Take X1, Y1 as top of triangle
	if (max == y1)
	{
		X1 = x1; Y1 = y1; colourTop = colour1;
		X0 = x2; Y0 = y2; c0 = colour2;
		X2 = x3; Y2 = y3; c2 = colour3;
	} else if (max == y2)
	{
		X1 = x2; Y1 = y2; colourTop = colour2;
		X0 = x1; Y0 = y1; c0 = colour1;
		X2 = x3; Y2 = y3; c2 = colour3;

	} else if (max == y3)
	{
		X1 = x3; Y1 = y3; colourTop = colour3;
		X0 = x1; Y0 = y1; c0 = colour1;
		X2 = x2; Y2 = y2; c2 = colour2;
	}
	double edgeA, edgeB;
	edgeA = atan2((double)Y2 - Y1, X2 - X1); 
	edgeB = atan2((double)Y0 - Y1, X0 - X1);	
	//Assign left/right edges 	
	if (edgeA > edgeB)
	{
		hLeft = Y1 - Y0;
		hRight = Y1 - Y2;
		XLeftVert = X0;
		YLeftVert = Y0;
		XRightVert = X2;
		YRightVert = Y2;
		colourLeft = c0;
		colourRight = c2;
	} else
	{
		hRight = Y1 - Y0;
		hLeft = Y1 - Y2;
		XLeftVert = X2;
		YLeftVert = Y2;
		XRightVert = X0;
		YRightVert = Y0;
		colourLeft = c2;
		colourRight = c0;
	}
	XTopVert = X1;
	YTopVert = Y1;
}

