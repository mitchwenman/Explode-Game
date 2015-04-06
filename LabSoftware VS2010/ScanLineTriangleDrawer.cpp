#include "ScanLineTriangleDrawer.h"
#include "LineDrawer.h"
#include <math.h>

namespace ScanLineTriangleDrawer
{
	void draw(ScanLineTriangle* tri)
	{
		//Assign left/right edges 
		double mL, mR;
		double mzL, mzR;
		mL = (tri->XLeftVert - tri->XTopVert)/
			((double)tri->YTopVert - tri->YLeftVert);
		mzL = (tri->ZLeftVert - tri->ZTopVert)/
			((double)tri->YTopVert - tri->YLeftVert);
		mR = (tri->XRightVert - tri->XTopVert)/
			((double)tri->YTopVert - tri->YRightVert);
		mzR = (tri->ZRightVert - tri->ZTopVert)/
			((double)tri->YTopVert - tri->YRightVert);

		//Calculate colour deltas - left first
		double redML, blueML, greenML;
		double leftDenom = tri->YTopVert - tri->YLeftVert;
		redML = ((double)tri->colourLeft->red - tri->colourTop->red)/leftDenom;
		blueML = ((double)tri->colourLeft->blue - tri->colourTop->blue)/leftDenom;
		greenML = ((double)tri->colourLeft->green - tri->colourTop->green)/leftDenom;

		//Then right
		double redMR, greenMR, blueMR;
		double rightDenom = tri->YTopVert - tri->YRightVert; 
		redMR = ((double)tri->colourRight->red - tri->colourTop->red)/rightDenom;
		blueMR = ((double)tri->colourRight->blue - tri->colourTop->blue)/rightDenom;
		greenMR = ((double)tri->colourRight->green - tri->colourTop->green)/rightDenom;
	
		//Assign starting point and check for flat top
		double xL, xR, zL, zR;
		double clRed, clBlue, clGreen, crRed, crGreen, crBlue;
		if (tri->YTopVert == tri->YLeftVert)
		{
			xL = tri->XLeftVert;
			zL = tri->ZLeftVert;
			clRed = tri->colourLeft->red;
			clGreen = tri->colourLeft->green;
			clBlue = tri->colourLeft->blue;
			xR = tri->XTopVert;
			zR = tri->ZTopVert;
			crRed = tri->colourTop->red;
			crGreen = tri->colourTop->green;
			crBlue = tri->colourTop->blue;
		} else if (tri->YTopVert == tri->YRightVert)
		{
			xL = tri->XTopVert;
			zL = tri->ZTopVert;
			clRed = tri->colourTop->red;
			clGreen = tri->colourTop->green;
			clBlue = tri->colourTop->blue;
		
			xR = tri->XRightVert;	
			zR = tri->ZRightVert;
			crRed = tri->colourRight->red;
			crGreen = tri->colourRight->green;
			crBlue = tri->colourRight->blue;
		} else 
		{
			xL = xR = tri->XTopVert;
			zL = zR = tri->ZTopVert;
			clRed = crRed = tri->colourTop->red;
			clGreen = crGreen = tri->colourTop->green;
			clBlue = crBlue = tri->colourTop->blue;
		}
	
		//Find longest edge for end point
		int high = (tri->hLeft > tri->hRight) ? tri->hLeft : tri->hRight;
		for (int y = 0; y < high; y++)
		{
			//If we've reached a new edge - modify gradient so we can draw it
 			if (y == tri->hLeft && tri->hRight - tri->hLeft == 0) break; //Only happens when flat bottom triangle
												//In which case - we're done anyway
			if (y == tri->hLeft) 
			{
				leftDenom = (double)(tri->hRight - tri->hLeft);
				mL = (tri->XRightVert - xL)/leftDenom;
				mzL = (tri->ZRightVert - zL)/leftDenom; 
				redML = ((double)tri->colourRight->red - tri->colourLeft->red)/leftDenom;
				blueML = ((double)tri->colourRight->blue - tri->colourLeft->blue)/leftDenom;
				greenML = ((double)tri->colourRight->green - tri->colourLeft->green)/leftDenom;
			}
			if (y == tri->hRight) 
			{
				rightDenom = (double)(tri->hLeft - tri->hRight);
				mR = (tri->XLeftVert - xR)/rightDenom;
				mzR = (tri->ZLeftVert - zR)/rightDenom;
				redMR = ((double)tri->colourLeft->red - tri->colourRight->red)/rightDenom;
				blueMR = ((double)tri->colourLeft->blue - tri->colourRight->blue)/rightDenom;
				greenMR = ((double)tri->colourLeft->green - tri->colourRight->green)/rightDenom;
			}
			//y is the y-Offset from the starting point Y1
			RGBColour cL = { (int)clRed, (int)clGreen, (int)clBlue };
			RGBColour cR = { (int)crRed, (int)crGreen, (int)crBlue };
			VERTEX_3D pL = { ceil(xL), tri->YTopVert - y, zL, &cL };
			VERTEX_3D pR = { ceil(xR - 1),  tri->YTopVert - y, zR, &cR };
			GPLine* line = new GPLine(pL, pR);
			LineDrawer::drawLine(line);
			xL += mL; xR += mR; 
			zL += mzL; zR += mzR;
			clRed += redML; clBlue += blueML; clGreen += greenML;
			crRed += redMR; crBlue += blueMR; crGreen += greenMR;
		}
	}
}