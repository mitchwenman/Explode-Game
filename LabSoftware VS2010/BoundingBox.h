#ifndef BOUNDINGBOX_
#define BOUNDINGBOX_

#include "GraphicsUtil.h"
#include "Polygon3D.h"

class BoundingBox
{
private:
	Polygon3D* p;

public:
	
	BoundingBox(Polygon3D* p) : p(p) {};
	~BoundingBox(void);

	//Returns the center point of a 3D object
	VERTEX_3D* calculateCenterPoint();

	//Returns the maximum X value in the set of vertices
	int findMaxX();

	//Returns the minimum X value in the set of vertices
	int findMinX();
	
	//Returns the maximum Y value in the set of vertices
	int findMaxY();

	//Returns the minimum X value in the set of vertices
	int findMinY();

	//Returns the maximum Z value in the set of vertices
	int findMaxZ();

	//Returns the minimum X value in the set of vertices
	int findMinZ();
};

#endif