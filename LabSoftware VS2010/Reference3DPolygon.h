#pragma once

#include "Polygon3D.h"
#include "GraphicsUtil.h"
#include <vector>

class Reference3DPolygon
{

public:
	Reference3DPolygon(Polygon3D* p);

	//The original polygon
	Polygon3D* originalPoly;

	//Surface normals for each face of the polygon
	std::vector<VERTEX_3D_f> normals;

	//Cumulative scale values for x, y and z axis
	double sx, sy, sz;

	//Cumulative orientation values
	int rx, ry, rz;

	//Current translation from original poly
	int tx, ty, tz;

	//Number of rotation operations
	int numRotates;
};