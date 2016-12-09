#pragma once

#include "BoundingBox.h"



namespace BoundingBoxDrawer
{
	const BYTE BOX_COLOUR_RED =		255;
	const BYTE BOX_COLOUR_GREEN =	255;
	const BYTE BOX_COLOUR_BLUE =	0;

	/******************
	Description: Draws the outline of a bounding box to the screen.
	Parameters: BoundingBox* box: The box to be drawn.	
	Preconditions: Input param is not NULL
	Postconditions: THe box is drawn to the frame buffer.
	Returns: void
	*******************/
	void draw(BoundingBox *box);
}