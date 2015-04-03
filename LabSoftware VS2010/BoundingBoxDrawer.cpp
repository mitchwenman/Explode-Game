#include "BoundingBoxDrawer.h"
#include "GPLine.h"
#include "GraphicsSettings.h"
#include "LineDrawer.h"

void BoundingBoxDrawer::draw(BoundingBox *box)
{
	int minX = box->findMinX();
	int minY = box->findMinY();
	int minZ = box->findMinZ();
	int maxX = box->findMaxX();
	int maxY = box->findMaxY();
	int maxZ = box->findMaxZ();
	const int num_edges = 12;
	GPLine *edges[num_edges];
	GraphicsSettings *gset = GraphicsSettings::getGraphicsSettings();
	int centrex = gset->getFrameWidth() / 2;
	int centrey = gset->getFrameHeight() / 2;
	int fov = 1000;
	RGBColour c = { BoundingBoxDrawer::BOX_COLOUR_RED, BoundingBoxDrawer::BOX_COLOUR_GREEN, BoundingBoxDrawer::BOX_COLOUR_BLUE };

	//Left, bottom, front - right, bottom, front
	edges[0] = new GPLine(minX * fov / (minZ + fov) + centrex, minY * fov / (minZ + fov) + centrey,
							maxX * fov / (minZ + fov) + centrex, minY * fov / (minZ + fov) + centrey);
	//Left, bottom, front - left, top, front
	edges[1] = new GPLine(minX * fov / (minZ + fov) + centrex, minY * fov / (minZ + fov) + centrey,
							minX * fov / (minZ + fov) + centrex, maxY * fov / (minZ + fov) + centrey);
	//Left, bottom, front - left, bottom, back
	edges[2] = new GPLine(minX * fov / (minZ + fov) + centrex, minY * fov / (minZ + fov) + centrey,
							minX * fov / (maxZ + fov) + centrex, minY * fov / (maxZ + fov) + centrey);
	//Right, bottom, front - right, top, front,
	edges[3] = new GPLine(maxX * fov / (minZ + fov) + centrex, minY * fov / (minZ + fov) + centrey,
							maxX * fov / (minZ + fov) + centrex, maxY * fov / (minZ + fov) + centrey);
	//Right, bottom, front - right, bottom, back
	edges[4] = new GPLine(maxX * fov / (minZ + fov) + centrex, minY * fov / (minZ + fov) + centrey,
							maxX * fov / (maxZ + fov) + centrex, minY * fov / (maxZ + fov) + centrey);
	//Right, bottom, back, - right, top, back
	edges[5] = new GPLine(maxX * fov / (maxZ + fov) + centrex, minY * fov / (maxZ + fov) + centrey,
							maxX * fov / (maxZ + fov) + centrex, maxY * fov / (maxZ + fov) + centrey);
	//Right, bottom, back, - left, bottom, back
	edges[6] = new GPLine(maxX * fov / (maxZ + fov) + centrex, minY * fov / (maxZ + fov) + centrey,
							minX * fov / (maxZ + fov) + centrex, minY * fov / (maxZ + fov) + centrey);
	//left, top, front - left, top, back
	edges[7] = new GPLine(minX * fov / (minZ + fov) + centrex, maxY * fov / (minZ + fov) + centrey,
							minX * fov / (maxZ + fov) + centrex, maxY * fov / (maxZ + fov) + centrey);
	//left, top, front - right, top front,
	edges[8] = new GPLine(minX * fov / (minZ + fov) + centrex, maxY * fov / (minZ + fov) + centrey,
							maxX * fov / (minZ + fov) + centrex, maxY * fov / (minZ + fov) + centrey);
	//right, top, back - left, top, back
	edges[9] = new GPLine(maxX * fov / (maxZ + fov) + centrex, maxY * fov / (maxZ + fov) + centrey,
							minX * fov / (maxZ + fov) + centrex, maxY * fov / (maxZ + fov) + centrey);
	//right, top, back - right, top, front
	edges[10] = new GPLine(maxX * fov / (minZ + fov) + centrex, maxY * fov / (minZ + fov) + centrey,
							maxX * fov / (maxZ + fov) + centrex, maxY * fov / (maxZ + fov) + centrey);
	//left, bottom, back - left, top, back
	edges[11] = new GPLine(minX * fov / (maxZ + fov) + centrex, minY * fov / (maxZ + fov) + centrey,
							minX * fov / (maxZ + fov) + centrex, maxY * fov / (maxZ + fov) + centrey);
	for (unsigned int i = 0; i < num_edges; i++)
	{
		edges[i]->c1 = edges[i]->c2 = &c;
		LineDrawer::drawLine(edges[i]);
	} 
	
}