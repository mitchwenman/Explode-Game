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
	int max = p->vertices[0].x;
	for (int i = 1; i < p->vertices.size(); i++)
	{
		if (p->vertices[i].x > max)
			max = p->vertices[i].x;
	}
	return max;
}

int BoundingBox::findMinX()
{
	int min = p->vertices[0].x;
	for (int i = 1; i < p->vertices.size(); i++)
	{
		if (p->vertices[i].x < min)
			min = p->vertices[i].x;
	}
	return min;
}
	
int BoundingBox::findMaxY()
{
	int max = p->vertices[0].y;
	for (int i = 1; i < p->vertices.size(); i++)
	{
		if (p->vertices[i].y > max)
			max = p->vertices[i].y;
	}
	return max;
}

int BoundingBox::findMinY()
{
	int min = p->vertices[0].y;
	for (int i = 1; i < p->vertices.size(); i++)
	{
		if (p->vertices[i].y < min)
			min = p->vertices[i].y;
	}
	return min;
}

int BoundingBox::findMaxZ()
{
	int max = p->vertices[0].z;
	for (int i = 1; i < p->vertices.size(); i++)
	{
		if (p->vertices[i].z > max)
			max = p->vertices[i].z;
	}
	return max;
}

int BoundingBox::findMinZ()
{
	int min = p->vertices[0].z;
	for (int i = 1; i < p->vertices.size(); i++)
	{
		if (p->vertices[i].z < min)
			min = p->vertices[i].z;
	}
	return min;
}