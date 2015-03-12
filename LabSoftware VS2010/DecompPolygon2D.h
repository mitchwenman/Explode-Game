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

	//Quick box test
	//Tests if left most point of testLine is within the box formed by
	//lines a, b and c.
	//Returns true if intersecting
	bool boxTest(POINT2D pA, POINT2D pB, POINT2D pC, POINT2D pTest);

	//Returns true if pTest is inside triangle formed by other points
	bool insideTest(POINT2D pA, POINT2D pB, POINT2D pC, POINT2D pTest);

	bool sameSide(POINT2D l1, POINT2D l2, POINT2D pA, POINT2D pB);

};

#endif