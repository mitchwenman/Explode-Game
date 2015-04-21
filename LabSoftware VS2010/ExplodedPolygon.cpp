///////////////////////////////////////////////////////////////////////////////////
// Filename: ExplodedPolygon.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Defines the exploded polygon constructor.
///////////////////////////////////////////////////////////////////////////////////


#include "ExplodedPolygon.h"


ExplodedPolygon::ExplodedPolygon(std::vector<VERTEX_3D> verts, VERTEX_3D_f traj)
{
	trajectory.x = traj.x;
	trajectory.y = traj.y;
	trajectory.z = traj.z;
	vertices = verts;
	std::vector<int> polyverts;
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		polyverts.push_back(i);
	}
	polygons.push_back(polyverts);
}


ExplodedPolygon::~ExplodedPolygon(void)
{
}
