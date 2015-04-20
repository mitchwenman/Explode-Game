#include "PixelDrawer.h"
#include "GPLine.h"
#include "GraphicsUtil.h"
#include "DDALine.h"

namespace LineDrawer
{
	/******************
	Description: Draws a line to the screen by calculating the required DDA values
	Parameters: GPLine* gpLine: the line to be drawn.
	Preconditions: Input param is not null.
	Postconditions: NIL
	Returns: void
	*******************///
	void drawLine(GPLine* gpLine);

	/******************
	Description: Clips the line to the screen boundary and calculates the dda values.
	Parameters: GPLine* gpLine: the line to be clipped.
	Preconditions: Input param is not null.
	Postconditions: NIL
	Returns: A clipped DDALine
	*******************///
	DDALine* calculateAndClipLine(GPLine* gpLine);

	/******************
	Description: Clips a line using liang-barsky.
	Parameters: GPLine* gpLine: the line to be clipped.
	Preconditions: Input param is not null.
	Postconditions: NIL
	Returns: The clipped line
	*******************///
	GPLine* clipLine(GPLine* line);

	/******************
	Description: Checks if a line requires clipping
	Parameters: GPLine* gpLine: the line to be tested
	Preconditions: Input param is not null.
	Postconditions: NIL
	Returns: True if the line requires clipping, else false
	*******************///
	bool lineNeedsClipping(GPLine* line);
	 
}