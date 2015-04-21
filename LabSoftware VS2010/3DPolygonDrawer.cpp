///////////////////////////////////////////////////////////////////////////////////
// Filename: 3DPolygonDrawer.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Implements the 3DPolygonDrawer namespace functions.
///////////////////////////////////////////////////////////////////////////////////


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
		int fov = gset->getFOV();
		for (int i = 0; i < p->polygons.size(); i++)
		{
			std::vector<VERTEX_3D> vList2d;
			std::vector<VERTEX_3D> vList3d = p->vertices;
			std::vector<int> polyVerts = p->polygons[i];
			for (int j = 0; j < polyVerts.size(); j++)
			{
				vList2d.push_back(convert3DVertexTo2DProjected(vList3d[polyVerts[j]]));
				
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

	bool isPolygonOffScreen(Polygon3D* polygon, int minimumZ, int maximumZ)
	{
		GraphicsSettings *gsettings = GraphicsSettings::getGraphicsSettings();
		int frameWidth = gsettings->getFrameWidth();
		int frameHeight = gsettings->getFrameHeight();
		int centerx = frameWidth / 2;
		int centery = frameHeight / 2;
		int fov = gsettings->getFOV();
		int pminx, pminy, pmaxx, pmaxy, pminz, pmaxz;
		std::vector<VERTEX_3D> verts = polygon->vertices;
		pminx = pmaxx = verts[0].x;
		pminy = pmaxy = verts[0].y;
		pminz = pmaxz = verts[0].z;
		for (unsigned int i = 1; i < verts.size(); i++)
		{
			int px = PolygonDrawer3D::projectXPoint(verts[i].x, verts[i].z, fov, centerx);
			int py = PolygonDrawer3D::projectYPoint(verts[i].y, verts[i].z, fov, centery);
			int z = verts[i].z;
			if (px < pminx) pminx = px;
			else if (px > pmaxx) pmaxx = px;
			if (py < pminy) pminy = py;
			else if (py > pmaxy) pmaxy = py;
			if (z < pminz) pminz = z;
			else if (z > pmaxz) pmaxz = z;
		}
		return (pmaxx < 0 || pminx > frameWidth ||
				pmaxy < 0 || pminy > frameHeight ||
				pmaxz < minimumZ ||
				pminz > maximumZ);
	}

	VERTEX_3D convert3DVertexTo2DProjected(VERTEX_3D vertex3d)
	{
		GraphicsSettings *gset = GraphicsSettings::getGraphicsSettings();
		int centrex = gset->getFrameWidth() / 2;
		int centrey = gset->getFrameHeight() / 2;
		int fov = gset->getFOV(); 
		int x = vertex3d.x;
		int y = vertex3d.y;
		int z = vertex3d.z;
		if (z <= -fov)
			z = -fov + 1;
		int newx = (int)projectXPoint(x, z, fov, centrex);
		int newy = (int)projectYPoint(y, z, fov, centrey);
		VERTEX_3D vert = { newx, newy, z, vertex3d.c };
		return vert;
	}

	double projectXPoint(double x, double z, int fov, int centerx)
	{
		return x * fov / (z + fov) + centerx;
	}

	double projectYPoint(double y, double z, int fov, int centery)
	{
		return y * fov / (z + fov) + centery;
	}
}
	
