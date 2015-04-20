#ifndef POLYGON3DROTATOR_
#define POLYGON3DROTATOR_

#include "Polygon3D.h"
#include "RotationConstantTable.h"
#include "GraphicsUtil.h"
#include <vector>

namespace Polygon3DRotator
{
	/******************
	Description: Rotates a polygon using coordiante-axis rotation by modifying it's vertices.
	Parameters: Polygon3D p: THe polygon to be rotated.
				int tx, ty, tz: The x, y, z rotation angles in degrees.
	Preconditions: NIL
	Postconditions: THe polygon's vertices will be modified.
	Returns:  void
	*******************///
	void Rotate(Polygon3D* p, int tx, int ty, int tz);

	/******************
	Description: Rotates a set of vertices by the amounts defined in the Rotation Constant table
	Parameters: vector<VERTEX_3D> vertices: The vertices to be transformed.
				RotationConstantTable* cTable: The rotation constant lookup table object.
	Preconditions: Input params not null.
	Postconditions: THe vertices will be modified.
	Returns:  void
	*******************///
	void RotateVertices(std::vector<VERTEX_3D>* vertices, RotationConstantTable* cTable);

	/******************
	Description: Rotates a set of vertices by the amounts defined in the Rotation Constant table
	Parameters: vector<VERTEX_3D_f> vertices: The vertices to be transformed.
				RotationConstantTable* cTable: The rotation constant lookup table object.
	Preconditions: Input params not null.
	Postconditions: THe vertices will be modified.
	Returns:  void
	*******************/
	void RotateVertices(std::vector<VERTEX_3D_f>* vertices, int rx, int ry, int rz);

	/******************
	Description: Rotates a single vertex by the amounts defined in the Rotation Constant table
	Parameters: VERTEX_3D vertex: The vertices to be transformed.
				RotationConstantTable* cTable: The rotation constant lookup table object.
	Preconditions: Input params not null.
	Postconditions: THe vertex will be modified.
	Returns:  void
	*******************/
	void RotateVertex(VERTEX_3D* vertex, RotationConstantTable* cTable);

	/******************
	Description: Rotates a single vertex by the amounts defined in the Rotation Constant table
	Parameters: VERTEX_3D_f vertex: The vertices to be transformed.
				RotationConstantTable* cTable: The rotation constant lookup table object.
	Preconditions: Input params not null.
	Postconditions: THe vertex will be modified.
	Returns:  void
	*******************/
	void RotateVertex(VERTEX_3D_f* vertex, RotationConstantTable* cTable);
}

#endif