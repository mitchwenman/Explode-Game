#pragma once

#include "BoundingBox.h"



namespace BoundingBoxDrawer
{
	const BYTE BOX_COLOUR_RED = 255;
	const BYTE BOX_COLOUR_GREEN = 255;
	const BYTE BOX_COLOUR_BLUE = 255;

	void draw(BoundingBox *box);
}