#include "Polygon3DScaler.h"
#include "BoundingBox.h"
#include "Polygon3DTranslator.h"
#include "GraphicsSettings.h"

void Polygon3DScaler::scale(Polygon3D* p, double sx, double sy, double sz)
{
	//Find center point
	BoundingBox* box = new BoundingBox(p);
	VERTEX_3D* origCenter = box->calculateCenterPoint();

	//Translate polygon back to origin
	GraphicsSettings *g = GraphicsSettings::getGraphicsSettings();
	int originX = g->getFrameWidth() / 2;
	int originY = g->getFrameHeight() / 2;
	Polygon3DTranslator::translate(p, -origCenter->x, -origCenter->y , -origCenter->z);
	//Scale each point
	for (int i = 0; i < p->vertices.size(); i++)
	{
		scalePoint(&p->vertices[i], sx, sy, sz);
	}
	//Find new centre point
	VERTEX_3D* newCenter = box->calculateCenterPoint();
	//Calculate old vs new center point difference
	int diffX = origCenter->x - newCenter->x;
	int diffY = origCenter->y - newCenter->y;
	int diffZ = origCenter->y - newCenter->y;
	//translate back
	Polygon3DTranslator::translate(p, diffX, diffY, diffZ);
	//cleanup
	delete(box);
	delete(newCenter);
	delete(origCenter);
}

void Polygon3DScaler::scalePoint(VERTEX_3D* v, double sx, double sy, double sz)
{
	v->x *= sx;
	v->y *= sy;
	v->z *= sz;
}