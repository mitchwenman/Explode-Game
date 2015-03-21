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
		int zoom = 150;
		for (int i = 0; i < p->polygons.size(); i++)
		{
			std::vector<VERTEX> vList2d;
			std::vector<VERTEX_3D*> vList3d = p->polygons[i];
			for (int j = 0; j < vList3d.size(); j++)
			{
				int z = vList3d[j]->z;
				VERTEX vert = { vList3d[j]->x / z * zoom + centrex, vList3d[j]->y / z * zoom + centrey, vList3d[j]->c };
				vList2d.push_back(vert);
			}
			Polygon2D* p = new Polygon2D(vList2d.size(), vList2d.data());
			PolygonDrawer::draw(p);
			delete(p);
		}
	}
}
	
