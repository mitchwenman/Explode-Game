#ifndef SCANLINETRIANGLEDRAWER_
#define SCANLINETRIANGLEDRAWER_

#include "ScanLineTriangle.h"

namespace ScanLineTriangleDrawer
{
	/******************
	Description:Draws a given scan line triangle object to the frame buffer using scan line filling.
	Parameters: ScanLineTriangle* tri: The triangle to be drawn.
	Preconditions: Input param not null.
	Postconditions: NIL
	Returns: void 
	*******************/
	void draw(ScanLineTriangle* tri);
}


#endif
