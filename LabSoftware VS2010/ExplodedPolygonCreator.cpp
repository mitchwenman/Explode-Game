///////////////////////////////////////////////////////////////////////////////////
// Filename: ExplodedPolygonCreator.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Creates an exploded polygon from an existing polygon.
///////////////////////////////////////////////////////////////////////////////////

//=======INCLUDES=========//
#include "ExplodedPolygonCreator.h"
#include "3DPolygonDrawer.h"


//=========FUNCTIONS========//

std::vector<ExplodedPolygon *> ExplodedPolygonCreator::explodePolygon(Polygon3D* poly, Reference3DPolygon* refPoly)
{
	//Calculate normal if needed
	if (refPoly->normals.size() == 0)
	{
		refPoly->calculateNormals();
	}
	std::vector<ExplodedPolygon *> explodedPolygons;
	explodedPolygons.reserve(poly->polygons.size());
	//Get the verts of each face and create an Exploded Poly with them
	for (unsigned int i = 0; i < poly->polygons.size(); i++)
	{
		std::vector<VERTEX_3D> polyVerts;
		for (unsigned int j = 0; j < poly->polygons[i].size(); j++)
		{
			polyVerts.push_back(poly->vertices[poly->polygons[i][j]]);
		}
		explodedPolygons.push_back(
			new ExplodedPolygon(polyVerts, refPoly->normals[i]));
	}	

	return explodedPolygons;
}

