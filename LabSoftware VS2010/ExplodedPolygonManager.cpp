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


void ExplodedPolygonManager::draw(bool shouldAnimate)
{
	for (unsigned int i = 0; i < explodedPolygons.size(); i++)
	{
		if (shouldAnimate)
			ExplodedPolygonAnimator::animateExplodedPolygon(explodedPolygons[i]);
		else
			PolygonDrawer3D::draw(explodedPolygons[i]);
	}
}

int ExplodedPolygonManager::cleanup() ///XXX: change to use 3Dpolygondrawer method
{
	int numDeleted = 0;
	for (unsigned int i = 0; i < explodedPolygons.size(); i++)
	{
		if (PolygonDrawer3D::isPolygonOffScreen(explodedPolygons[i],
												MIN_Z_RENDER,
												MAX_Z_BEFORE_CLEANUP))
		{
			delete(explodedPolygons[i]);
			explodedPolygons.erase(explodedPolygons.begin() + i);
			i--; //So we don't skip any when we erase
		}
	}

	return numDeleted;
}

void ExplodedPolygonManager::reset()
{
	while (!explodedPolygons.empty())
	{
		delete(explodedPolygons[0]);
		explodedPolygons.erase(explodedPolygons.begin());
	}
}


int ExplodedPolygonManager::explodePolygonAtCoords(int x, int y)
{
	int index = ExplodedPolygonManager::polygonAtCoords(x, y);
	if (index != -1)
	{
		Polygon3DManager *polymanager = Polygon3DManager::getSingleton();
	
		Polygon3D *poly = polymanager->getPolygon3Ds()[index];
		Reference3DPolygon *refPoly = polymanager->getReferencePolygons()[index];
		std::vector<ExplodedPolygon *> expPolys = ExplodedPolygonCreator::explodePolygon(poly, refPoly);
		explodedPolygons.insert(explodedPolygons.end(), expPolys.begin(), expPolys.end()); //append to end of vector
		polymanager->removePolygonAtIndex(index);
	}
	
	return index;
}

int ExplodedPolygonManager::polygonAtCoords(int x, int y)
{

	GraphicsSettings *gsettings = GraphicsSettings::getGraphicsSettings();
	int centerx = gsettings->getFrameWidth() / 2;
	int centery = gsettings->getFrameHeight() / 2;
	y = gsettings->getFrameHeight() - y;
	int fov = gsettings->getFOV();
	int pminx, pminy, pmaxx, pmaxy;
	unsigned int index = 0;
	
	Polygon3DManager *polymanager = Polygon3DManager::getSingleton();
	std::vector<Polygon3D *> polys = polymanager->getPolygon3Ds();
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