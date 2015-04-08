#include "ExplodedPolygonManager.h"
#include "BoundingBox.h"
#include "World.h"
#include "3DPolygonDrawer.h"
#include "GraphicsSettings.h"
#include <iostream> //XXX: delete this

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
	int index = ExplodedPolygonManager::polygonAtCoords(x, y);
	std::cout << index << std::endl;
	return index;
}

int ExplodedPolygonManager::polygonAtCoords(int x, int y)
{
	GraphicsSettings *gsettings = GraphicsSettings::getGraphicsSettings();
	int centerx = gsettings->getFrameWidth() / 2;
	int centery = gsettings->getFrameHeight() / 2;
	int fov = gsettings->getFOV();
	int pminx, pminy, pmaxx, pmaxy;
	unsigned int index = 0;
	
	World *world = World::getSingleton();
	std::vector<Polygon3D *> polys = world->polygon3ds;
	//For each polygon in the world
	for ( ; index < polys.size(); index++)
	{
		Polygon3D *pol = polys[index];
		if (pol != NULL)
		{
			std::vector<VERTEX_3D> verts = pol->vertices;
			pminx = pmaxx = PolygonDrawer3D::projectXPoint(verts[0].x, verts[0].z, fov, centerx);
			pminy = pmaxy = PolygonDrawer3D::projectYPoint(verts[0].y, verts[0].z, fov, centery);
			for (unsigned int i = 1; i < verts.size(); i++)
			{
				int px = PolygonDrawer3D::projectXPoint(verts[i].x, verts[i].z, fov, centerx);
				int py = PolygonDrawer3D::projectYPoint(verts[i].y, verts[i].z, fov, centery);
				if (px < pminx) pminx = px;
				else if (px > pmaxx) pmaxx = px;
				if (py < pminy) pminy = py;
				else if (py > pmaxy) pmaxy = py;
			}
		}	
		if (x <= pmaxx && x >= pminx &&
			y <= pmaxy && y >= pminy)
			break; //break loop so we can return this index
		
	}
		
	return (index < polys.size()) ? index : -1;
}