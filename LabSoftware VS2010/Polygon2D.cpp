#include "Polygon2D.h"

Polygon2D::Polygon2D(int numSides, GPLine* sides[]) : numSides(numSides) 
{
	this->sides.assign(sides, sides + numSides);
}

Polygon2D::Polygon2D(int numVerts, POINT2D verts[])
{
	for (int i = 0; i < numVerts - 1; i++)
	{
		this->sides.push_back(new GPLine(verts[i].x, verts[i].y, verts[i + 1].x, verts[i + 1].y));
	}
	this->sides.push_back(new GPLine(verts[numVerts - 1].x, verts[numVerts - 1].y, verts[0].x, verts[0].y));
	this->numSides = numVerts;
}