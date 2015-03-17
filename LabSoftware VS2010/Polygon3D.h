#ifndef POLYGON3D_
#define POLYGON3D_

#include "GraphicsUtil.h"
#include <vector>

class Polygon3D
{

public:

	Polygon3D() { };

	std::vector<VERTEX_3D> vertices;

	std::vector<std::vector<VERTEX_3D*>> polygons;

};


#endif