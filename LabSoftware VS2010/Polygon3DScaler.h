#ifndef POLYGON3DSCALER_
#define POLYGON3DSCALER_

#include "Polygon3D.h"
#include "GraphicsUtil.h"

namespace Polygon3DScaler
{
	void scale(Polygon3D* p, double sx, double sy, double sz);

	void scalePoint(VERTEX_3D* v, double sx, double sy, double sz);
}

#endif