#include "Polygon3DManager.h"

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

}

//Removes any polygons not on the screen anymore
//Returns the number of polygons removed
int Polygon3DManager::cleanup()
{
	int numDeleted = 0;
	return numDeleted;
}

//Adds a new polygon to the vector if is ready to
//Polygons will be added to the vector more regularly as time progresses
//Returns the newly created polygon or NULL if one wasn't created
Polygon3D* Polygon3DManager::addNewPolygonIfReady()
{
	return NULL;
}

//Applys a set of transformations to the polygon
void Polygon3DManager::applyTransformations(Polygon3D* polygon, std::vector<PolygonTransformation> transformations)
{

}
