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

	//Projects a vertex onto the screen using a viewing transformation
	//Z value remains unchanged.
	VERTEX_3D convert3DVertexTo2DProjected(VERTEX_3D vertex3d);

	//Returns true if the polygon is not visible on the screen
	//Variable min/max Z values provides flexibility to caller
	bool isPolygonOffScreen(Polygon3D* polygon, int minimumZ, int maximumZ);

	//Projects an X coordinate value onto the screen
	double projectXPoint(double x, double z, int fov, int centerx);

	//Projects a Y coordinate value onto the screen
	double projectYPoint(double y, double z, int fov, int centery);
}

#endif