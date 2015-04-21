///////////////////////////////////////////////////////////////////////////////////
// Filename: Reference3DPolygon.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Creates a reference for a 3DPolygon, i.e. to reset it. Also stores surface normals.
///////////////////////////////////////////////////////////////////////////////////


#include "Reference3DPolygon.h"
#include "SurfaceNormal.h"

Reference3DPolygon::Reference3DPolygon(Polygon3D* p) : sx(1), sy(1), sz(1), tx(0), ty(0), tz(0), rx(0), ry(0), rz(0), numRotates(0)
{
	this->originalPoly = new Polygon3D(*p);
}

void Reference3DPolygon::calculateNormals()
{
	std::vector<VERTEX_3D> verts = originalPoly->vertices;
	for (unsigned int i = 0; i < originalPoly->polygons.size(); i++)
	{
		std::vector<int> face = originalPoly->polygons[i];
		VERTEX_3D_f* normal = SurfaceNormal::calculateSurfaceNormal(verts[face[0]],
																  verts[face[1]],
																  verts[face[2]]);
		this->normals.push_back(*normal);
	}
}