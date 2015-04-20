#pragma once

#include <vector>
#include "GraphicsUtil.h"

namespace SurfaceNormal
{
	/******************
	Description: Calculates the surface normal of a plane defined by three points.
	Parameters: VERTEX_3D v1, v2, v3: The vectors defining the plane.
	Preconditions: v1, v2, v3 not collinear or equal.
	Postconditions: NIL
	Returns:  The surface normal of the plane.
	*******************/
	VERTEX_3D_f* calculateSurfaceNormal(VERTEX_3D v1, VERTEX_3D v2, VERTEX_3D v3);
}