///////////////////////////////////////////////////////////////////////////////////
// Filename: Polygon2D.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Constructors for Polygon2D class.
///////////////////////////////////////////////////////////////////////////////////

#include "Polygon2D.h"

Polygon2D::Polygon2D(int numSides, GPLine* sides[]) : numSides(numSides) 
{
	this->sides.assign(sides, sides + numSides);
}

Polygon2D::Polygon2D(int numVerts, VERTEX_3D verts[])
{
	for (int i = 0; i < numVerts - 1; i++)
	{
		this->sides.push_back(new GPLine(verts[i], verts[i + 1]));
	}
	this->sides.push_back(new GPLine(verts[numVerts - 1], verts[0]));
	this->numSides = numVerts;
}

Polygon2D::~Polygon2D()
{
	for (unsigned int i = 0; i < sides.size(); i++)
	{
		delete(sides[i]);		
	}
	sides.clear();
}