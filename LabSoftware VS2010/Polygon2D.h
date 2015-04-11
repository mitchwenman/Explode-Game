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

	//Default constructor
	Polygon2D() {};

	~Polygon2D();

	//Creates a polygon from a list of edges
	Polygon2D(int numSides, GPLine* sides[]);

	//Creates a polygon from a list of vertices
	Polygon2D(int numVerts, VERTEX_3D verts[]);
};


#endif