#include "ExplodedPolygonCreator.h"

std::vector<ExplodedPolygon *> ExplodedPolygonCreator::explodePolygon(Polygon3D* poly, Reference3DPolygon* refPoly)
{
	std::vector<ExplodedPolygon *> explodedPolygons;
	explodedPolygons.reserve(poly->polygons.size());
	//Convert each face to a projected X, projected Y and projected Z

	//Create the exploded polygon

	return explodedPolygons;
}

std::vector<ExplodedPolygon *> ExplodedPolygonCreator::explodeAndDestroyPolygon(Polygon3D* poly, Reference3DPolygon* refPoly)
{
	std::vector<ExplodedPolygon *> explodedPolygons = ExplodedPolygonCreator::explodePolygon(poly, refPoly);
	delete(poly);
	delete(refPoly);
	return explodedPolygons;
}