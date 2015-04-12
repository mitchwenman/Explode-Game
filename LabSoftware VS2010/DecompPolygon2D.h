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

	~DecompPolygon2D(); 

	//Quick box test
	//Tests if left most point of testLine is within the box formed by
	//lines a, b and c.
	//Returns true if intersecting
	bool boxTest(VERTEX_3D pA, VERTEX_3D pB, VERTEX_3D pC, VERTEX_3D pTest);

	//Returns 1 if test.x1/y1 intersects, 2 if x2/y2 or 0 if doesn't intersect
	int insideTest(GPLine* a, GPLine* b, GPLine* c, GPLine* test);

	//Returns true if pTest is inside triangle formed by other points
	bool insideTest(VERTEX_3D pA, VERTEX_3D pB, VERTEX_3D pC, VERTEX_3D pTest);

	//Returns true if VERTEX_3D A and B are on the same side of the line
	//formed by l1 and l2
	bool sameSide(VERTEX_3D l1, VERTEX_3D l2, VERTEX_3D pA, VERTEX_3D pB);

	//Decomposes a list of edges into a set of triangles
	void decompose();

	//Returns the index of the next line to be used
	//to form a triangle
	int findLeftMostLineIndex();

	//Finds an adjacent line to the line at lineAInd
	int findAdjacentLineIndex(int lineAInd);

	//Returns a the index of the line with the given coordinates
	//If not found returns -1
	int DecompPolygon2D::findLineWithCoords(VERTEX_3D p1, VERTEX_3D p2);

	//Custom comparison function for sorting
	static bool compare(GPLine* a, GPLine* b);

};

#endif