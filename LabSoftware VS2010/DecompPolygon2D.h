#ifndef DECOMPPOLYGON2D_
#define DECOMPPOLYGON2D_

#include "Polygon2D.h"
#include "ScanLineTriangle.h"
#include "GraphicsUtil.h"

class DecompPolygon2D : public Polygon2D
{

public:
	std::vector<GPLine*> decompSides;
	std::vector<ScanLineTriangle* > triangles;

	//Transforms and decomposes normal polygon
	DecompPolygon2D(Polygon2D* p);

	//Quick box test - use first before inside test
	//Tests if left most point of testLine is within the box formed by
	//lines a, b and c.
	//Returns true if intersecting
	bool boxTest(POINT2D pA, POINT2D pB, POINT2D pC, POINT2D pTest);

	//Secondary inside test
	bool insideTest(POINT2D pA, POINT2D pB, POINT2D pC, POINT2D pTest);


};

#endif