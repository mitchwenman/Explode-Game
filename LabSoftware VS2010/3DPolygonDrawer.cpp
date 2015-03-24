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
		int zoom = 500;
		for (int i = 0; i < p->polygons.size(); i++)
		{
			std::vector<VERTEX> vList2d;
			std::vector<VERTEX_3D*> vList3d = p->polygons[i];
			
			for (int j = 0; j < vList3d.size(); j++)
			{
				int tx = vList3d[j]->x - centrex;
				int ty = vList3d[j]->y - 700;
				int z = vList3d[j]->z;
				int newx = tx * zoom / (z + zoom);
				int newy = ty * zoom / (z + zoom);
				VERTEX vert = { ((newx + centrex) * zoom) / (zoom +  z), ((newy + 700) * zoom)/(zoom + z), vList3d[j]->c };
				vList2d.push_back(vert);
			}
			Polygon2D* p2d = new Polygon2D(vList2d.size(), vList2d.data());
			PolygonDrawer::draw(p2d);
			delete(p2d);
		}
	}
}
	
