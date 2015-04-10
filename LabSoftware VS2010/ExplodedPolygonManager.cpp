#include "ExplodedPolygonManager.h"
#include "BoundingBox.h"
#include "Polygon3DManager.h"
#include "3DPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "ExplodedPolygonCreator.h"
#include "ExplodedPolygonAnimator.h"
#include "ZBuffer.h"

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
	for (unsigned int i = 0; i < explodedPolygons.size(); i++)
	{
		ExplodedPolygonAnimator::animateExplodedPolygon(explodedPolygons[i]);
	}
}

int ExplodedPolygonManager::cleanup() ///XXX: change to use 3Dpolygondrawer method
{
	GraphicsSettings *gsettings = GraphicsSettings::getGraphicsSettings();
	int frameWidth = gsettings->getFrameWidth();
	int frameHeight = gsettings->getFrameHeight();
	int centerx = frameWidth / 2;
	int centery = frameHeight / 2;
	int fov = gsettings->getFOV();
	//For every polygon
	for (unsigned int j = 0; j < explodedPolygons.size(); j++)
	{
		int pminx, pminy, pmaxx, pmaxy, pminz, pmaxz;
		ExplodedPolygon *poly = explodedPolygons[j];
		std::vector<VERTEX_3D> verts = poly->vertices;
		pminx = pmaxx = verts[0].x;
		pminy = pmaxy = verts[0].y;
		pminz = pmaxz = verts[0].z;
		for (unsigned int i = 1; i < verts.size(); i++)
		{
			int px = PolygonDrawer3D::projectXPoint(verts[i].x, verts[i].z, fov, centerx);
			int py = PolygonDrawer3D::projectYPoint(verts[i].y, verts[i].z, fov, centery);
			int z = verts[i].z;
			if (px < pminx) pminx = px;
			else if (px > pmaxx) pmaxx = px;
			if (py < pminy) pminy = py;
			else if (py > pmaxy) pmaxy = py;
			if (z < pminz) pminz = z;
			else if (z > pmaxz) pmaxz = z;
		}
		//If not on screen then delete
		if (pmaxx < 0 || pminx > frameWidth ||
			pmaxy < 0 || pminy > frameHeight ||
			pmaxz > MAX_Z_BEFORE_CLEANUP ||
			pminz < MIN_Z_RENDER)
		{
			delete(poly);
			explodedPolygons.erase(explodedPolygons.begin() + j);
		}
	}	

	return 0;
}

int ExplodedPolygonManager::explodePolygonAtCoords(int x, int y)
{
	int index = ExplodedPolygonManager::polygonAtCoords(x, y);
	if (index != -1)
	{
		World *world = World::getSingleton();
		Polygon3D *poly = world->polygon3ds[index];
		Reference3DPolygon *refPoly = world->originalPolygons[index];
		std::vector<ExplodedPolygon *> expPolys = ExplodedPolygonCreator::explodePolygon(poly, refPoly);
		explodedPolygons.insert(explodedPolygons.end(), expPolys.begin(), expPolys.end()); //append to end of vector
		world->remove3DPolyAtPosition(index);
	}
	
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
			if (x <= pmaxx && x >= pminx &&
				y <= pmaxy && y >= pminy)
			break; //break loop so we can return this index
		
		}	
		
	}		
	return (index < polys.size()) ? index : -1;
}