#pragma once

#include <vector>
#include "ExplodedPolygon.h"
#include "Polygon3D.h"
#include "Reference3DPolygon.h"

namespace ExplodedPolygonCreator
{
	/******************
	Description: Creates a set of 3d polygon fragments from a given polygon
	Parameters: Polygon3D* poly: The polygon from which the fragments will be created
				Reference3DPolygon refPoly: The reference polygon where the trajectory will be taken from it's normals
	Preconditions: refPoly->polygon = poly
	Postconditions: NIL
	Returns: A vector of 3d polygon fragments.
	*******************/
	std::vector<ExplodedPolygon *> explodePolygon(Polygon3D* poly, Reference3DPolygon* refPoly);

}