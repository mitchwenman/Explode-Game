#pragma once

#include <vector>
#include "ExplodedPolygon.h"
#include "Polygon3D.h"
#include "Reference3DPolygon.h"

namespace ExplodedPolygonCreator
{
	//Returns a vector of new exploded polygons with their trajectory
	//defined by their normal
	std::vector<ExplodedPolygon *> explodePolygon(Polygon3D* poly, Reference3DPolygon* refPoly);

}