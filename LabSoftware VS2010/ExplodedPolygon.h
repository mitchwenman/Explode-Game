#pragma once
#include "Polygon2D.h"

class ExplodedPolygon :	public Polygon2D
{

public:
	VERTEX_3D_f trajectory;

	ExplodedPolygon(int numVerts, VERTEX_3D verts[], VERTEX_3D_f traj);
	~ExplodedPolygon(void);
};

