#ifndef POLYGON3DROTATOR_
#define POLYGON3DROTATOR_

#include "Polygon3D.h"
#include "RotationConstantTable.h"
#include "GraphicsUtil.h"
#include <vector>

namespace Polygon3DRotator
{
	//Rotates a polygon using coordinate-axis rotation
	void Rotate(Polygon3D* p, int tx, int ty, int tz);

	//Rotates a set of vertices
	void RotateVertices(std::vector<VERTEX_3D>, RotationConstantTable* cTable);

	void RotateVertices(std::vector<VERTEX_3D_f>, RotationConstantTable* cTable);

	//Rotates a single vertex using a given constant table
	void RotateVertex(VERTEX_3D vertex, RotationConstantTable* cTable);

	void RotateVertex(VERTEX_3D_f vertex, RotationConstantTable* cTable);
}

#endif