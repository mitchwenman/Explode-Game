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

	/******************
	Description: Clips and draws the 2D polygon to the frame buffer
	Parameters: Polygon2D *p: The polygon to be drawn.
	Preconditions: Input param(s) not null.
	Postconditions: NIL
	Returns:  void
	*******************/
	void draw(Polygon2D* p);

	/******************
	Description: Clips a polygon using Sutherland-Hodgeman clipping
	Parameters: Polygon2D *p: The polygon to be clipped.
				int leftEdge, topEdge, rightEdge, BottomEdge: The edges of the clipping boundary. X values for left/right. Y values for top/bottom
	Preconditions: Input param(s) not null.
	Postconditions: NIL
	Returns:  The clipped polygon
	*******************/
	Polygon2D* clipPolygon(Polygon2D* p, int leftEdge, int topEdge, int rightEdge, int bottomEdge);

	/******************
	Description: Clips a polygon against a horizontal boundary.
	Parameters: vector<VERTEX_3D> input: The input vertex list.
				int boundary: The y value of the boundary.
				ClipType c: Whether it's a maximum or minimum boundary.
	Preconditions: Input param(s) not null.
	Postconditions: NIL
	Returns:  A list of clipped vertices.
	*******************/
	std::vector<VERTEX_3D> clipHorizontal(std::vector<VERTEX_3D> input, int boundary, ClipType c);

	/******************
	Description: Clips a polygon against a vertical boundary.
	Parameters: vector<VERTEX_3D> input: The input vertex list.
				int boundary: The x value of the boundary.
				ClipType c: Whether it's a maximum or minimum boundary.
	Preconditions: Input param(s) not null.
	Postconditions: NIL
	Returns:  A list of clipped vertices.
	*******************/
	std::vector<VERTEX_3D> clipVertical(std::vector<VERTEX_3D> input, int boundary, ClipType c);

}

#endif