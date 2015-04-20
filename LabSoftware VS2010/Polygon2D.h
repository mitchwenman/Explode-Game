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

	/******************
	Description: Constructor.
	Parameters: int numSides:	The number of edges of the polygon
				GLine* sides[]: The edge array of the polygon
	Preconditions: Input params not null
	Postconditions: NIL
	Returns: 
	*******************///
	Polygon2D(int numSides, GPLine* sides[]);

	/******************
	Description: Constructor.
	Parameters: int numVerts:	The number of vertices of the polygon
				VERTEX_3D* verts[]: The vertex array of the polygon
	Preconditions: Input params not null
	Postconditions: NIL
	Returns: 
	*******************///
	Polygon2D(int numVerts, VERTEX_3D verts[]);
};


#endif