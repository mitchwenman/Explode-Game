#ifndef POLYGON2D_
#define POLYGON2D_

#include "GPLine.h"
#include <vector>

class Polygon2D
{

public:
	int numSides;
	std::vector<GPLine*> sides;

	Polygon2D(int numSides, GPLine* sides[]);
};


#endif