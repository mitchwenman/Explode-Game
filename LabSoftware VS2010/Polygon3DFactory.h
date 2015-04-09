#pragma once

#include "Polygon3D.h"
#include "PolygonDatabase.h"
#include "GraphicsUtil.h"

/*
 * A namespace for the creation of new polygons by copying from the PolygonDatabase
 * Can create a set of random operations for each created polygon
 */

namespace Polygon3DFactory
{
	const int DIST_LEFT_OFFSCREEN_START = -400; //The distance away from the left of the screen (-X)
													//that the poly should start from

	const int MIN_DIST_TOP_START = 200; //The minimum distance from the top of the screen
										//that the polygon should start from.

	const int MIN_DIST_BOTTOM_START = 200; //The minimum distance from the bottom of the screen

	const int MIN_Z_START = 200; //Minimum z value for polygon to start

	const int MAX_Z_START = 800; //Max z value

	//Returns a new copy of a random polygon from the database
	Polygon3D* createRandomPolygonFromDatabase();

	//Creates a random starting point for a new polygon
	VERTEX_3D_f getRandomStartingPoint();

};