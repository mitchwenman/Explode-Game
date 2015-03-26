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

	VERTEX_3D* calculateCenterPoint();

	int findMaxX();

	int findMinX();
	
	int findMaxY();

	int findMinY();

	int findMaxZ();

	int findMinZ();
};

#endif