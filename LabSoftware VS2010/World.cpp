#include "World.h"
#include "GraphicsSettings.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DTranslator.h"

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
	//Add difference
	int dx = x - width/2;
	int dy = y - height/2;
	int dz = z;
	//Translate
	Polygon3DTranslator::translate(p, dx, dy, dz);
	//Draw
	PolygonDrawer3D::draw(p);

}