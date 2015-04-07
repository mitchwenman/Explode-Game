#include "ExplodedPolygon.h"


ExplodedPolygon::ExplodedPolygon(int numVerts, VERTEX_3D verts[], VERTEX_3D_f traj) : Polygon2D(numVerts, verts)
{
	trajectory.x = traj.x;
	trajectory.y = traj.y;
	trajectory.z = traj.z;
}


ExplodedPolygon::~ExplodedPolygon(void)
{
}
