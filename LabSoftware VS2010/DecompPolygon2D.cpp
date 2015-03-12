#include <math.h>

#include "DecompPolygon2D.h"

#ifdef _WIN32
	#include <windows.h>
#endif

DecompPolygon2D::DecompPolygon2D(Polygon2D* p)
{
	this->numSides = p->numSides;
	this->sides = p->sides;
	this->decompSides.assign(sides.begin(), sides.end());
	this->triangles.reserve(p->numSides - 2);
}

//Returns true if point intersects
bool DecompPolygon2D::boxTest(POINT2D pA, POINT2D pB, POINT2D pC, POINT2D pTest)
{
	int leftEdge, rightEdge, topEdge, bottomEdge;
	leftEdge = min(min(pA.x, pB.x), pC.x);
	rightEdge = max(max(pA.x, pB.x), pC.x);
	topEdge = max(max(pA.y, pB.y), pC.y);
	bottomEdge = min(min(pA.y, pB.y), pC.y);
	//Test
	bool outside = false;
	outside = pTest.x < leftEdge || pTest.x > rightEdge;
	outside = outside || pTest.y < bottomEdge || pTest.y > topEdge;	
	
	return !outside;
}

bool DecompPolygon2D::insideTest(POINT2D pA, POINT2D pB, POINT2D pC, POINT2D pTest)
{
	if (!boxTest(pA, pB, pC, pTest)) 
		return true;
	else
		return sameSide(pA, pB, pC, pTest) &&
				sameSide(pA, pC, pB, pTest) &&
				sameSide(pB, pC, pA, pTest);
}

bool DecompPolygon2D::sameSide(POINT2D l1, POINT2D l2, POINT2D pA, POINT2D pB)
{
	double apt = (l2.x - l1.x) * (pA.y - l1.y) - (l2.y - l1.y) * (pA.x - l1.x);
	double bpt = (l2.x - l1.x) * (pB.y - l1.y) - (l2.y - l1.y) * (pB.x - l1.x);
	//int apt = (pA.x-l1.x) * (l2.y-l1.y) - (l2.x-l1.x) * (pA.y-l1.y);
	//int bpt = (pB.x-l1.x) * (l2.y-l1.y) - (l2.x-l1.x) * (pB.y- l1.y);
	return ((apt * bpt) > 0);
}
