#include "ExplodedPolygonManager.h"
#include "BoundingBox.h"
#include "World.h"

static ExplodedPolygonManager *_instance;

ExplodedPolygonManager* ExplodedPolygonManager::getSingleton()
{
	if (!_instance)
	{
		_instance = new ExplodedPolygonManager();
	}
	return _instance;
}


void ExplodedPolygonManager::draw()
{
}

int ExplodedPolygonManager::cleanup()
{
	return 0;
}

int ExplodedPolygonManager::explodePolygonAtCoords(int x, int y)
{
	return -1;
}

int ExplodedPolygonManager::polygonAtCoords(int x, int y)
{
	return -1;
}