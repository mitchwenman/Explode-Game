#include "Polygon2D.h"

Polygon2D::Polygon2D(int numSides, GPLine* sides[]) : numSides(numSides) 
{
	this->sides.assign(sides, sides + numSides);
}

Polygon2D::Polygon2D(int numVerts, VERTEX verts[])
{
	for (int i = 0; i < numVerts - 1; i++)
	{
		this->sides.push_back(new GPLine(verts[i], verts[i + 1]));
	}
	this->sides.push_back(new GPLine(verts[numVerts - 1], verts[0]));
	this->numSides = numVerts;
}