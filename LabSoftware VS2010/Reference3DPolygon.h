#pragma once

#include "Polygon3D.h"

class Reference3DPolygon
{

public:

	//The original polygon
	Polygon3D* originalPoly;

	//Cumulative scale values for x, y and z axis
	double sx, sy, sz;

	//Cumulative orientation values
	int rx, ry, rz;

	//Current translation from original poly
	int tx, ty, tz;

	//
};