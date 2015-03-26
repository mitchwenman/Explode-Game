#include "BoundingBox.h"



BoundingBox::~BoundingBox(void)
{
}

VERTEX_3D* BoundingBox::calculateCenterPoint()
{
	int xmax = findMaxX();
	int xmin = findMinX();
	int ymax = findMaxY();
	int ymin = findMinY();
	int zmax = findMaxZ();
	int zmin = findMinZ();
	VERTEX_3D* v = new VERTEX_3D();
	v->x = xmin + ((xmax - xmin) / 2);
	v->y = ymin + ((ymax - ymin) / 2);
	v->z = zmin + ((zmax - zmin) / 2);
	return v;
}

int BoundingBox::findMaxX()
{
	return 200;
}

int BoundingBox::findMinX()
{
	return 0;
}
	
int BoundingBox::findMaxY()
{
	return 200;
}

int BoundingBox::findMinY()
{
	return 0;
}

int BoundingBox::findMaxZ()
{
	return 200;
}

int BoundingBox::findMinZ()
{
	return 0;
}