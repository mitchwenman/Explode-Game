#ifndef WORLD_
#define WORLD_

#include "Polygon3D.h"
#include "3DPolygonDrawer.h"

#include <vector>

class World
{

private:
	std::vector<Polygon3D *> polygon3ds;
	
	World() { };

public:
	static World* getSingleton();

	void insert3DPolyAtPosition(Polygon3D* p, int x, int y, int z);


};


#endif