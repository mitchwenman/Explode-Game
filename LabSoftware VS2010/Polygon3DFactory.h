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
	//Returns a new copy of a random polygon from the database
	Polygon3D* createRandomPolygonFromDatabase();

	//Creates a random starting point for a new polygon
	VERTEX_3D_f getRandomStartingPoint();

};