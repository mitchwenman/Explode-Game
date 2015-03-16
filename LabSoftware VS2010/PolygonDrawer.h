#ifndef POLYGONDRAWER_
#define POLYGONDRAWER_

#include "GraphicsSettings.h"
#include "Polygon2D.h"


namespace PolygonDrawer
{
	void draw(Polygon2D* p);

	Polygon2D* clipPolygon(Polygon2D* p);

}

#endif