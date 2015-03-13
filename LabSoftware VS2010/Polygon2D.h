#ifndef POLYGON2D_
#define POLYGON2D_

#include "GPLine.h"
#include "GraphicsUtil.h"
#include <vector>

class Polygon2D
{

public:
	int numSides;
	std::vector<GPLine*> sides;

	Polygon2D() {};
	Polygon2D(int numSides, GPLine* sides[]);
	Polygon2D(int numVerts, POINT2D verts[]);
};


#endif