#include "Polygon3DManager.h"
#include "Polygon3DFactory.h"
#include "3DPolygonDrawer.h"
#include "BoundingBox.h"
#include "Polygon3DTranslator.h"
#include "ZBuffer.h"

static Polygon3DManager* _instance;

Polygon3DManager* Polygon3DManager::getSingleton()
{
	if (!_instance)
		_instance = new Polygon3DManager();
	return _instance;
}

//Draws the current 3d polygons to the frame buffer
void Polygon3DManager::animate()
{
	for (unsigned int i = 0; i < polygon3ds.size(); i++)
	{
		applyTransformations(polygon3ds[i], referencePolygons[i], transformations[i]);
		PolygonDrawer3D::draw(polygon3ds[i], referencePolygons[i]);
	}
}

//Removes any polygons not on the screen anymore
//Returns the number of polygons removed
int Polygon3DManager::cleanup()
{
	int numDeleted = 0;
	for (unsigned int i = 0; i < polygon3ds.size(); i++)
	{
		if (PolygonDrawer3D::isPolygonOffScreen(polygon3ds[i], MIN_Z_RENDER, MAX_Z_RENDER))
		{
			removePolygonAtIndex(i);
			numDeleted++;
		}
	}
	return numDeleted;
}

void Polygon3DManager::removePolygonAtIndex(int i)
{
	if (i >= 0 && i < polygon3ds.size())
	{
		polygon3ds.erase(polygon3ds.begin() + i);
		transformations.erase(transformations.begin() + i);
		referencePolygons.erase(referencePolygons.begin() + i);
	}
	
}

//Adds a new polygon to the vector if is ready to
//Polygons will be added to the vector more regularly as time progresses
//Returns the newly created polygon or NULL if one wasn't created
Polygon3D* Polygon3DManager::addNewPolygonIfReady()
{
	Polygon3D* newPoly = NULL;
	if ((polygonCreationCounter++ % POLYGON_CREATION_INTERVAL) == 0)
	{
		Polygon3DFactory* factory = Polygon3DFactory::getSingleton();
		newPoly = factory->createRandomPolygonFromDatabase();
		VERTEX_3D_f startingPoint = factory->getRandomStartingPoint();
		//Translate to starting point
		//Create bounding box
		BoundingBox* bbox = new BoundingBox(newPoly);
		VERTEX_3D* v = bbox->calculateCenterPoint();
		//Add difference
		int dx = startingPoint.x - v->x;
		int dy = startingPoint.y - v->y;
		int dz = startingPoint.z - v->z;
		//Translate
		Polygon3DTranslator::translate(newPoly, dx, dy, dz);
		Reference3DPolygon *refP = new Reference3DPolygon(newPoly);
		refP->calculateNormals();
		polygon3ds.push_back(newPoly);
		transformations.push_back(factory->getRandomTransformationSet());
		referencePolygons.push_back(refP);
	}
	return newPoly;
}

//Applys a set of transformations to the polygon
void Polygon3DManager::applyTransformations(Polygon3D* polygon, Reference3DPolygon* refP, std::vector<PolygonTransformation> transformations)
{
	for (unsigned int i = 0; i < transformations.size(); i++)
		transformations[i].apply(polygon, refP);
}
