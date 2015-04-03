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
	GPLine *edges[12];
	GraphicsSettings *gset = GraphicsSettings::getGraphicsSettings();
	int centrex = gset->getFrameWidth() / 2;
	int centrey = gset->getFrameHeight() / 2;
	int fov = 1000;
	RGBColour c = { BoundingBoxDrawer::BOX_COLOUR_RED, BoundingBoxDrawer::BOX_COLOUR_GREEN, BoundingBoxDrawer::BOX_COLOUR_BLUE };

	//Left, bottom, back - right, bottom, back
	edges[0] = new GPLine(minX * fov / (minZ + fov) + centrex, minY * fov / (minZ + fov) + centrey,
							maxX * fov / (minZ + fov) + centrex, minY * fov / (minZ + fov) + centrey);
	//Left, bottom, back - left, top, back

	//Left, bottom, back - left, bottom, front

	//Right, bottom, back - right, top, back,

	//Right, bottom, back - right, bottom, front

	//Right, bottom, front, - right, top, front

	//Right, bottom, front, - left, bottom, front

	//left, top, back - left, top, front

	//left, top, back - right, top back,

	//right, top, front - left, top, front

	//right, top, front - right, top, back


	LineDrawer::drawLine(edges[0]);
}