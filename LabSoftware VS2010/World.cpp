#include "World.h"
#include "GraphicsSettings.h"
#include "GraphicsUtil.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DTranslator.h"
#include "BoundingBox.h"

static World* _instance;

World* World::getSingleton()
{
	if (!_instance)
	{
		_instance = new World();
	}
	return _instance;
}

void World::insert3DPolyAtPosition(Polygon3D* p, int x, int y, int z)
{
	//Get frame height/width
	GraphicsSettings* gset = GraphicsSettings::getGraphicsSettings();
	int width = gset->getFrameWidth();
	int height = gset->getFrameHeight();
	//Create bounding box
	BoundingBox* bbox = new BoundingBox(p);
	VERTEX_3D* v = bbox->calculateCenterPoint();
	//Add difference
	int dx = x - v->x;
	int dy = y - v->y;
	int dz = z - v->z;
	//Translate
	Polygon3DTranslator::translate(p, dx, dy, dz);
	
	this->polygon3ds.push_back(p);
}