#ifndef POLYGONDRAWER_
#define POLYGONDRAWER_

#include "GraphicsSettings.h"
#include "Polygon2D.h"
#include "GraphicsUtil.h"

#include <vector>

namespace PolygonDrawer
{
	//Used for less than/greater than logic
	//when clipping against a boundary
	enum ClipType { MIN, MAX }; 

	//Draws a clipped 3D polygon to the screen
	void draw(Polygon2D* p);

	//Uses Sutherland-Hodgman polygon clipping to a clip a given polygon
	//against 4 boundaries
	Polygon2D* clipPolygon(Polygon2D* p, int leftEdge, int topEdge, int rightEdge, int bottomEdge);

	//Clips a polygon against a horizontal boundary (top and bottom of the screen)
	std::vector<VERTEX_3D> clipHorizontal(std::vector<VERTEX_3D> input, int boundary, ClipType c);

	//Clips a polygon against a vertical boundary (left and right of the screen)
	std::vector<VERTEX_3D> clipVertical(std::vector<VERTEX_3D> input, int boundary, ClipType c);

}

#endif