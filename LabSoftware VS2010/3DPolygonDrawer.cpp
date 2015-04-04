#include "3DPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "PolygonDrawer.h"
#include "Polygon3D.h"
#include "Polygon2D.h"
#include "GraphicsUtil.h"

#include <vector>

namespace PolygonDrawer3D
{
	//Draws a 3D polygon
	void draw(Polygon3D* p)
	{
		GraphicsSettings *gset = GraphicsSettings::getGraphicsSettings();
		int centrex = gset->getFrameWidth() / 2;
		int centrey = gset->getFrameHeight() / 2;
		int fov = 1000;
		for (int i = 0; i < p->polygons.size(); i++)
		{
			std::vector<VERTEX> vList2d;
			std::vector<VERTEX_3D> vList3d = p->vertices;
			std::vector<int> polyVerts = p->polygons[i];
			for (int j = 0; j < polyVerts.size(); j++)
			{
				int x = vList3d[polyVerts[j]].x;
				int y = vList3d[polyVerts[j]].y;
				int z = vList3d[polyVerts[j]].z;
				if (z <= -fov)
					z = -fov + 1;
				int newx = x * fov / (z + fov) + centrex;
				int newy = y * fov / (z + fov) + centrey;
				VERTEX vert = { newx, newy, vList3d[polyVerts[j]].c };
				vList2d.push_back(vert);

				
			}
			if (vList2d.size() != 0)
			{
				Polygon2D* p2d = new Polygon2D(vList2d.size(), vList2d.data());
				PolygonDrawer::draw(p2d);
				delete(p2d);
			}
			
		}
	}

	void draw(Polygon3D* p, Reference3DPolygon* refP)
	{
		Polygon3D* culledPolygon = new Polygon3D();
		culledPolygon->vertices = p->vertices;
		for (unsigned int i = 0; i < p->polygons.size(); i++)
		{
			//if z value of normal is <= 0 add to polygon (else it's a backface)
			if (refP->normals[i].z <= 0)
			{
				culledPolygon->polygons.push_back(p->polygons[i]);
			}
		}
		draw(culledPolygon);
		delete(culledPolygon);
	}
}
	
