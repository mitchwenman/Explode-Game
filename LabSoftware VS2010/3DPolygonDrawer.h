#ifndef POLYGON3DDRAWER_
#define POLYGON3DDRAWER_

#include "Polygon3D.h"
#include "Reference3DPolygon.h"

namespace PolygonDrawer3D 
{
	/******************
	Description: Draws a 3D polygon to the screen
	Parameters: Polygon3D* p;	The polygon to be drawn
	Preconditions: p must not be NULL
	*******************/
	void draw(Polygon3D* p);

	/******************
	Description: Draws a 3D polygon and performs backface culling
	Parameters: Polygon3D*			p: The polygon to be drawn
				Reference3DPolygon*	refP: The corresponding refernce polygon containing the polygon's normals.
	Preconditions: refP->polygon == p
	Postconditions: NIL
	******************/
	void draw(Polygon3D* p, Reference3DPolygon* refP);

	/******************
	Description: Projects a vertex onto the screen using a viewing transformation
					Z value remains unchanged.
	Parameters: VERTEX_3D vertex3d: THe vertex to be projected.
	Preconditions: Input params are not NULL.
	Postconditions: NIL
	Returns: THe projected vertex
	******************/
	VERTEX_3D convert3DVertexTo2DProjected(VERTEX_3D vertex3d);

	/******************
	Description: Returns true if the polygon is not visible on the screen
					Variable min/max Z values provides flexibility to caller
	Parameters: Polygon3D* polygon: Input polygon
				int			minz:	Minimum z value
				int			maxz:	Maximum z value
	Preconditions: Input params are not NULL.
	Postconditions: NIL
	Returns: True if the polygon is off screen, else false.
	*******************/
	bool isPolygonOffScreen(Polygon3D* polygon, int minimumZ, int maximumZ);

	/******************
	Description: Projects an X coordinate onto the screen
	Parameters: double	x: THe x coord
				double	z: THe z coord
				int		fov: The field of view
				int		centerx: The centre X value.
	Preconditions: Input params are not NULL.
	Postconditions: NIL
	Returns: A projected X coordinate
	*******************/
	double projectXPoint(double x, double z, int fov, int centerx);

	/******************
	Description: Projects an Y coordinate onto the screen
	Parameters: double	y: THe y coord
				double	z: THe z coord
				int		fov: The field of view
				int		centery: The centre Y value.
	Preconditions: Input params are not NULL.
	Postconditions: NIL
	Returns: A projected Y coordinate
	*******************/
	double projectYPoint(double y, double z, int fov, int centery);
}

#endif