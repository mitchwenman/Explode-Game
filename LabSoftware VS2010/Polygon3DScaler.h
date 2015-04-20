#ifndef POLYGON3DSCALER_
#define POLYGON3DSCALER_

#include "Polygon3D.h"
#include "GraphicsUtil.h"

namespace Polygon3DScaler
{
	/******************
	Description: Scales a polygon by modifying its vertices.
	Parameters: Polygon* p: THe polygon to be transformed.
				double sx, sy, sz: The scaling factors for x, y, z axis.
	Preconditions: Input params not null.
	Postconditions: THe polygon's vertices will be modified.
	Returns:  void
	*******************/
	void scale(Polygon3D* p, double sx, double sy, double sz);

	/******************
	Description: Scales a single vertex
	Parameters: VERTEX_3D vertex: The vertex to be transformed.
				double sx, sy, sz: The scaling factors for x, y, z axis.
	Preconditions: Input params not null.
	Postconditions: THe vertex will be modified.
	Returns:  void
	*******************/
	void scalePoint(VERTEX_3D* v, double sx, double sy, double sz);
}

#endif