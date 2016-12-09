#ifndef POLYGON3DTRANSLATOR_
#define POLYGON3DTRANSLATOR_

#include "Polygon3D.h"

namespace Polygon3DTranslator
{
	/******************
	Description: Translates a polygon by modifying its vertices.
	Parameters: Polygon* p: THe polygon to be transformed.
				int dx, dy, dz: The translation for x, y, z axis.
	Preconditions: Input params not null.
	Postconditions: THe polygon's vertices will be modified.
	Returns:  void
	*******************/
	void translate(Polygon3D* p, int dx, int dy, int dz);

	/******************
	Description: Translates a vertex
	Parameters: VERTEX_3D* p: The vertex to be modified.
				int dx, dy, dz: The translation for x, y, z axis.
	Preconditions: Input params not null.
	Postconditions: THe vertex will be modified.
	Returns:  void
	*******************/
	void translatePoint(VERTEX_3D* p, int dx, int dy, int dz);
}


#endif