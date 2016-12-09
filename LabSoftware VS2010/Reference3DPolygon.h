#pragma once

#include "Polygon3D.h"
#include "GraphicsUtil.h"
#include <vector>

class Reference3DPolygon
{

public:

	/******************
	Description:Constructor
	Parameters: Polygon3D* polygon: The polygon this contains information about.
	Preconditions: Input param(s) not null.
	Postconditions: NIL
	Returns:  
	*******************/
	Reference3DPolygon(Polygon3D* p);

	/******************
	Description:Calculates the normals of each polygon face and stores them in normals.
	Parameters: NIL
	Preconditions: this->originalPoly is not null.
	Postconditions: this->normals contains the polygon's normals.
	Returns:  void
	*******************/
	void calculateNormals();

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