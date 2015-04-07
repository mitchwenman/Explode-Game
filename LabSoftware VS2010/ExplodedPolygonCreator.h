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

	//Returns a vector of new exploded polygons with their trajectory
	//defined by their normal. Invokes delete on the original 3D polygon and reference polygon
	std::vector<ExplodedPolygon *> explodeAndDestroyPolygon(Polygon3D* poly, Reference3DPolygon* refPoly);
}