#ifndef POLYGONDRAWER_
#define POLYGONDRAWER_

#include "GraphicsSettings.h"
#include "Polygon2D.h"
#include "GraphicsUtil.h"

#include <vector>

namespace PolygonDrawer
{
	enum ClipType { MIN, MAX }; //Used for less than/greater than logic

	void draw(Polygon2D* p);

	Polygon2D* clipPolygon(Polygon2D* p);

	Polygon2D* clipPolygon2(Polygon2D* p, int leftEdge, int topEdge, int rightEdge, int bottomEdge);

	std::vector<VERTEX> clipHorizontal(std::vector<VERTEX> input, int boundary, ClipType c);

	std::vector<VERTEX> clipVertical(std::vector<VERTEX> input, int boundary, ClipType c);

}

#endif