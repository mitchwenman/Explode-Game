#pragma once
#include "Polygon3D.h"

class ExplodedPolygon :	public  Polygon3D
{

public:
	VERTEX_3D_f trajectory;

	ExplodedPolygon(std::vector<VERTEX_3D> verts, VERTEX_3D_f traj);
	~ExplodedPolygon(void);
};

