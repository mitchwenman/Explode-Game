#include "DecompPolygon2D.h"

DecompPolygon2D::DecompPolygon2D(Polygon2D* p)
{
	this->numSides = p->numSides;
	this->sides = p->sides;
	this->decompSides.assign(sides.begin(), sides.end());
	this->triangles.reserve(p->numSides - 2);
}

bool DecompPolygon2D::boxTest(GPLine* lineA, GPLine* lineB, GPLine* lineC, GPLine* testLine)
{
	return false;
}