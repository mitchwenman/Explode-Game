#include "Polygon3DScaler.h"
#include "BoundingBox.h"
#include "Polygon3DTranslator.h"
#include "GraphicsSettings.h"

void Polygon3DScaler::scale(Polygon3D* p, double sx, double sy, double sz)
{
	//Find center point
	BoundingBox* box = new BoundingBox(p);
	VERTEX_3D* origCenter = box->calculateCenterPoint();
	delete(box);
	//Translate polygon back to origin
	GraphicsSettings *g = GraphicsSettings::getGraphicsSettings();
	Polygon3DTranslator::translate(p, -origCenter->x, -origCenter->y , -origCenter->z);
	//Scale each point
	for (int i = 0; i < p->vertices.size(); i++)
	{
		scalePoint(&p->vertices[i], sx, sy, sz);
	}
	int diffX = origCenter->x;
	int diffY = origCenter->y;
	int diffZ = origCenter->z;
	//translate back
	Polygon3DTranslator::translate(p, diffX, diffY, diffZ);
	//cleanup
	delete(origCenter);
}

void Polygon3DScaler::scalePoint(VERTEX_3D* v, double sx, double sy, double sz)
{
	v->x *= sx;
	v->y *= sy;
	v->z *= sz;
}