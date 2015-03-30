#include "World.h"
#include "GraphicsSettings.h"
#include "GraphicsUtil.h"
#include "3DPolygonDrawer.h"
#include "PolygonDrawer.h"
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

void World::insert2DPoly(Polygon2D* p)
{
	this->polygon2ds.push_back(p);
}

void World::drawWorld()
{
	for (unsigned int i = 0; i < this->polygon2ds.size(); i++)
	{
		PolygonDrawer::draw(this->polygon2ds[i]);
	}
	for (unsigned int i = 0; i < this->polygon3ds.size(); i++)
	{
		PolygonDrawer3D::draw(this->polygon3ds[i]);

	}
}