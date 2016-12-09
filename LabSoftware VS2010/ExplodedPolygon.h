#pragma once
#include "Polygon3D.h"

class ExplodedPolygon :	public  Polygon3D
{

public:
	VERTEX_3D_f trajectory;

	/******************
	Description: Constructor.
	Parameters: vector<VERTEX_3D> verts: The list of vertices in order.
				VERTEX_3D_f		  traj:  The trajectory of the polygon.
	Preconditions: NIL
	Postconditions: NIL
	Returns: 
	*******************/
	ExplodedPolygon(std::vector<VERTEX_3D> verts, VERTEX_3D_f traj);
	~ExplodedPolygon(void);
};

