#include "Polygon2D.h"

Polygon2D::Polygon2D(int numSides, GPLine* sides[]) : numSides(numSides) 
{
	this->sides.assign(sides, sides + numSides);
}