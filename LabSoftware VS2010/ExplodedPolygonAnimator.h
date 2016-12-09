#pragma once

#include "ExplodedPolygon.h"
#include "PolygonDrawer.h"

namespace ExplodedPolygonAnimator
{
	const int DEFAULT_SPEED = 100;

	/******************
	Description: Translates the polygon by it's trajectory and draws it to the screen.
	Parameters: ExplodedPolygon *poly: The polygon to be drawn
	Preconditions: NIL
	Postconditions: The polygons vertices will be modified.
	Returns: void
	*******************/
	void animateExplodedPolygon(ExplodedPolygon *poly);
}