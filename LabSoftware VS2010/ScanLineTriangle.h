#include "RGBColor.h"

class ScanLineTriangle
{

public:
	int XTopVert, YTopVert, XLeftVert, YLeftVert, XRightVert, YRightVert;
	int hRight, hLeft;
	RGBColour* colourTop, *colourLeft, *colourRight; 

	ScanLineTriangle(int x1, int y1, int x2, int y2, int x3, int y3, 
						RGBColour* colour1, RGBColour* colour2, RGBColour* colour3);

	void draw(BYTE* frameBuffer);
};
