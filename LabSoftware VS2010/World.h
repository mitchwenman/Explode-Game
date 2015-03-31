#ifndef WORLD_
#define WORLD_

#include "Polygon3D.h"
#include "Polygon2D.h"
#include "3DPolygonDrawer.h"

#include <vector>

class World
{

private:
	//Constructor
	World() { };

public:

	std::vector<Polygon3D *> polygon3ds;
	std::vector<Polygon2D *> polygon2ds;

	//Creates if needed and returns the World singleton object
	static World* getSingleton();

	//Translates the polygon such that the centre of the polygon is
	//at the given coordinates and adds it to the 3D poly vector
	void insert3DPolyAtPosition(Polygon3D* p, int x, int y, int z);

	//Adds the polygon to the 2D poly vector
	void insert2DPoly(Polygon2D* p);

	//Draws the 2D and 3D to the frame buffer stored in GraphicsSettings
	void drawWorld();


};


#endif