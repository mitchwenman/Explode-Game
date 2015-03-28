#ifndef WORLD_
#define WORLD_

#include "Polygon3D.h"
#include "Polygon2D.h"
#include "3DPolygonDrawer.h"

#include <vector>

class World
{

private:	
	World() { };

public:
	std::vector<Polygon3D *> polygon3ds;
	std::vector<Polygon2D *> polygon2ds;

	static World* getSingleton();

	void insert3DPolyAtPosition(Polygon3D* p, int x, int y, int z);

	void insert2DPoly(Polygon2D* p);


};


#endif