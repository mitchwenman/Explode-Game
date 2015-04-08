#ifndef POLYGON3D_
#define POLYGON3D_

#include "GraphicsUtil.h"
#include <vector>

class Polygon3D
{

public:

	Polygon3D() { };

	//The list of vertices that make up the polygon
	std::vector<VERTEX_3D> vertices;

	//A vector, with each element containing a vector of indices
	//to the vertices that make up that polygon
	std::vector<std::vector<int>> polygons;

};


#endif