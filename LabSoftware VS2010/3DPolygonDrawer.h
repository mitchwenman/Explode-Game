#ifndef POLYGON3DDRAWER_
#define POLYGON3DDRAWER_

#include "Polygon3D.h"
#include "Reference3DPolygon.h"

namespace PolygonDrawer3D 
{
	//Draws a given 3D polygon
	void draw(Polygon3D* p);

	//Draws a 3d polygon and performs backface culling
	void draw(Polygon3D* p, Reference3DPolygon* refP);

	VERTEX_3D convert3DVertexTo2DProjected(VERTEX_3D vertex3d);

	double projectXPoint(double x, double z, int fov, int centerx);

	double projectYPoint(double y, double z, int fov, int centery);
}

#endif