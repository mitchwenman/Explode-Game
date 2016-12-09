///////////////////////////////////////////////////////////////////////////////////
// Filename: ScanLineTriangle.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Creates and calculates the values for a scan line triangle.
///////////////////////////////////////////////////////////////////////////////////

//=======INCLUDES=========//
#ifdef _WIN32
	#include <windows.h>
#endif

#include <math.h>
#include "ScanLineTriangle.h"

//=========FUNCTIONS========//

ScanLineTriangle::ScanLineTriangle(int x1, int y1, int z1, int x2, int y2, int z2,
									int x3, int y3, int z3, 
									RGBColour colour1, RGBColour colour2, RGBColour colour3)
{
	int X0, X1, X2, Y0, Y1, Y2, Z0, Z1, Z2; //For holding vertices after (highest) is found
	RGBColour c0, c2; 
	int max = max(max(y1, y2), y3);
	//Reassign to vars for rest of alg to work
	//Take X1, Y1 as top of triangle
	if (max == y1)
	{
		X1 = x1; Y1 = y1; Z1 = z1; colourTop = colour1;
		X0 = x2; Y0 = y2; Z0 = z2; c0 = colour2;
		X2 = x3; Y2 = y3; Z2 = z3; c2 = colour3;
	} else if (max == y2)
	{
		X1 = x2; Y1 = y2; Z1 = z2; colourTop = colour2;
		X0 = x1; Y0 = y1; Z0 = z1; c0 = colour1;
		X2 = x3; Y2 = y3; Z2 = z3; c2 = colour3;

	} else if (max == y3)
	{
		X1 = x3; Y1 = y3; Z1 = z3; colourTop = colour3;
		X0 = x1; Y0 = y1; Z0 = z1; c0 = colour1;
		X2 = x2; Y2 = y2; Z2 = z2; c2 = colour2;
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
		ZLeftVert = Z0;
		XRightVert = X2;
		YRightVert = Y2;
		ZRightVert = Z2;
		colourLeft = c0;
		colourRight = c2;
	} else
	{
		hRight = Y1 - Y0;
		hLeft = Y1 - Y2;
		XLeftVert = X2;
		YLeftVert = Y2;
		ZLeftVert = Z2;
		XRightVert = X0;
		YRightVert = Y0;
		ZRightVert = Z0;
		colourLeft = c2;
		colourRight = c0;
	}
	XTopVert = X1;
	YTopVert = Y1;
	ZTopVert = Z1;
}

