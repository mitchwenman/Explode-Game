#include "ExplodedPolygonCreator.h"
#include "3DPolygonDrawer.h"

std::vector<ExplodedPolygon *> ExplodedPolygonCreator::explodePolygon(Polygon3D* poly, Reference3DPolygon* refPoly)
{
	std::vector<ExplodedPolygon *> explodedPolygons;
	explodedPolygons.reserve(poly->polygons.size());
	//Convert each face to a projected X, projected Y and projected Z
	for (unsigned int i = 0; i < poly->polygons.size(); i++)
	{
		std::vector<VERTEX_3D> polyVerts;
		for (unsigned int j = 0; j < poly->polygons[i].size(); j++)
		{
			polyVerts.push_back(
				PolygonDrawer3D::convert3DVertexTo2DProjected(poly->vertices[poly->polygons[i][j]]));
		}
		explodedPolygons.push_back(new ExplodedPolygon(polyVerts.size(), polyVerts.data(), refPoly->normals[i]));
	}
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