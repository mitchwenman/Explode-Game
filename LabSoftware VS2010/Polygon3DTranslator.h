#ifndef POLYGON3DTRANSLATOR_
#define POLYGON3DTRANSLATOR_

#include "Polygon3D.h"

namespace Polygon3DTranslator
{
	//Translates each vertex of a polygon
	void translate(Polygon3D* p, int dx, int dy, int dz);

	//Translates a vertex
	void translatePoint(VERTEX_3D* p, int dx, int dy, int dz);
}


#endif