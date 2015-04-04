#ifndef POLYGON3DDRAWER_
#define POLYGON3DDRAWER_

#include "Polygon3D.h"
#include "Reference3DPolygon.h"

namespace PolygonDrawer3D 
{
	//Draws a given 3D polygon
	void draw(Polygon3D* p);

	//Draws a 3d polygon and performs backface culling
	void draw(Polygon3D* p, ReferencePolygon* refP);
}

#endif