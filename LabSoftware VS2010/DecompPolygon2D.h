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

	/******************
	Description: DecompPolygon constructor
	Parameters: Polygon2D* p: The polygon to be decomposed
	Preconditions: Input param is not null.
	Postconditions: NIL
	Returns: 
	*******************/
	DecompPolygon2D(Polygon2D* p);

	~DecompPolygon2D(); 



	/******************
	Description: Tests if ptest falls within the box formed by pa, pb, pc
	Parameters: VERTEX_3D pa, pb, pc: The boundaries of the box.
				VERTEX_3D		pTest: The test point.
	Preconditions: Input params are not null.
	Postconditions: NIL
	Returns: True if ptest falls within the boundaries, else false.
	*******************/
	bool boxTest(VERTEX_3D pA, VERTEX_3D pB, VERTEX_3D pC, VERTEX_3D pTest);

	/******************
	Description: Tests if ptest falls within the points pa, pb, pc.
	Parameters: VERTEX_3D pa, pb, pc: The boundaries of the triangle.
				VERTEX_3D		pTest: The test point.
	Preconditions: Input params are not null.
	Postconditions: NIL
	Returns: True if ptest falls within the boundaries, else false.
	*******************/
	//Returns true if pTest is inside triangle formed by other points
	bool insideTest(VERTEX_3D pA, VERTEX_3D pB, VERTEX_3D pC, VERTEX_3D pTest);

	/******************
	Description: Tests if pa and pb are on the same side of the line formed by l1, l2
	Parameters: VERTEX_3D l1, l2: The boundaries of the triangle.
				VERTEX_3D	pa, pb: The test points.
	Preconditions: Input params are not null.
	Postconditions: NIL
	Returns: True if pa and pb are on the same side, else false.
	*******************/
	bool sameSide(VERTEX_3D l1, VERTEX_3D l2, VERTEX_3D pA, VERTEX_3D pB);

	/******************
	Description: Decomposes a shape into triangles
	Parameters: NIL
	Preconditions: NIL
	Postconditions: this->triangles is the list of triangles.
	Returns: void
	*******************/
	void decompose();

	/******************
	Description: Finds the line in edge vector with left most vertex.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: The index in decompSides of the left most line.
	*******************/
	int findLeftMostLineIndex();

	/******************
	Description: Finds the line in edge vector that is adjacent to the line at the given index.
	Parameters: int lineAInd: the index of the line that should be adjacent to the found line.
	Preconditions: NIL
	Postconditions: NIL
	Returns: The index in decompSides of the line adjacent.
	*******************/
	int findAdjacentLineIndex(int lineAInd);

	/******************
	Description: Finds the index of the line with the given coords.
	Parameters: VERTEX_3D p1, p2: The points defining the line.
	Preconditions: NIL
	Postconditions: NIL
	Returns: The index in decompSides with the given coordinates
	*******************/
	int DecompPolygon2D::findLineWithCoords(VERTEX_3D p1, VERTEX_3D p2);

	/******************
	Description: Determines the left most of two lines
	Parameters: GPLine *a, *b: The lines to be compared.
	Preconditions: NIL
	Postconditions: NIL
	Returns: True if line a is more left than b, else false
	*******************/
	static bool compare(GPLine* a, GPLine* b);

};

#endif