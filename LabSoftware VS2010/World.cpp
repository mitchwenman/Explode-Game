#include "World.h"
#include "GraphicsSettings.h"
#include "GraphicsUtil.h"
#include "3DPolygonDrawer.h"
#include "PolygonDrawer.h"
#include "Polygon3DTranslator.h"
#include "BoundingBox.h"
#include "Reference3DPolygon.h"
#include "Polygon3DScaler.h"
#include "Polygon3DRotator.h"
#include "BoundingBoxDrawer.h"
#include "SurfaceNormal.h"
#include "ExplodedPolygonManager.h"
#include "Polygon3DManager.h"
#include "ZBuffer.h"


static World* _instance;

World* World::getSingleton()
{
	if (!_instance)
	{
		_instance = new World();
	}
	return _instance;
}

int World::insert3DPoly(Polygon3D* p, int x, int y, int z)
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
	//Create a reference polygon - calculate normals
	Reference3DPolygon* refP = new Reference3DPolygon(p);
	std::vector<VERTEX_3D> verts = p->vertices;
	for (unsigned int i = 0; i < p->polygons.size(); i++)
	{
		std::vector<int> face = p->polygons[i];
		VERTEX_3D_f* normal = SurfaceNormal::calculateSurfaceNormal(verts[face[0]],
																  verts[face[1]],
																  verts[face[2]]);
		refP->normals.push_back(*normal);
	}
	this->originalPolygons.push_back(refP);
	return polygon3ds.size() - 1;

}

void World::remove3DPolyAtPosition(int i)
{
	if (i >= 0 && i < polygon3ds.size() && polygon3ds[i] != NULL)
	{
		delete(polygon3ds[i]);
		polygon3ds[i] = NULL;
	}
}

void World::insert2DPoly(Polygon2D* p)
{
	this->polygon2ds.push_back(p);
}

void World::drawWorld()
{
	bool shouldAnimate = GraphicsSettings::getGraphicsSettings()->shouldAnimate();
	Polygon3DManager *manager = Polygon3DManager::getSingleton();
	if (shouldAnimate) //Tie creation of polygons to frame rate
	{
		manager->cleanup();
		manager->addNewPolygonIfReady();
	}
	manager->animate(shouldAnimate);	
	ExplodedPolygonManager *expmanager = ExplodedPolygonManager::getSingleton();
	expmanager->draw(shouldAnimate);
	if (shouldAnimate)
		expmanager->cleanup();
	ZBuffer::getSingleton()->flush();
}

void World::translate3DPolyAtIndex(int i, int dx, int dy, int dz)
{
	if (i >= 0 && i < polygon3ds.size())
	{
		Polygon3D *p = polygon3ds[i];
		if (p != NULL)
		{
			Reference3DPolygon *refP = originalPolygons[i];
			Polygon3DTranslator::translate(p, dx, dy, dz);
			refP->tx += dx;
			refP->ty += dy;
			refP->tz += dz;
		}
		
	}
	
}

void World::rotate3DPolyAtIndex(int i, int dx, int dy, int dz)
{
	if (i >= 0 && i < polygon3ds.size())
	{
		Polygon3D *p = polygon3ds[i];
		if (p != NULL)
		{
			Reference3DPolygon *refP = originalPolygons[i];
			refP->numRotates++;
			refP->rx += dx;
			refP->ry += dy;
			refP->rz += dz;
			if (false)//refP->numRotates > N_ROTATES_BEFORE_REDRAW)
			{
				refP->numRotates = 0;
				delete(polygon3ds[i]);
				p = new Polygon3D(*refP->originalPoly);
				polygon3ds[i] = p;
			
				Polygon3DScaler::scale(p, refP->sx, refP->sy, refP->sz);
				Polygon3DRotator::Rotate(p, refP->rx % 360, refP->ry % 360, refP->rz % 360);
				Polygon3DTranslator::translate(p, refP->tx, refP->ty, refP->tz);
			} else
			{
				Polygon3DRotator::Rotate(p, dx, dy, dz);
				Polygon3DRotator::RotateVertices(&refP->normals, dx, dy, dz);
			
			}
		}
		
			
		
		
	}
}

void World::scale3DPolyAtIndex(int i, double sx, double sy, double sz)
{
	if (i >= 0 && i < polygon3ds.size())
	{
		Polygon3D *p = polygon3ds[i];
		Reference3DPolygon *refP = originalPolygons[i];
		Polygon3DScaler::scale(p, sx, sy, sz);
		refP->sx *= sx;
		refP->sy *= sy;
		refP->sz *= sz;
	}
}