#include "Polygon3DFactory.h"
#include "GraphicsSettings.h"
#include <stdlib.h> //Rand

namespace Polygon3DFactory
{
	//Returns a new copy of a random polygon from the database
	Polygon3D* createRandomPolygonFromDatabase()
	{
		return NULL;
	}

	//Creates a random starting point for a new polygon
	VERTEX_3D_f getRandomStartingPoint()
	{
		GraphicsSettings* gsettings = GraphicsSettings::getGraphicsSettings();
		int frameHeight = gsettings->getFrameHeight();
		double y = std::rand() % (frameHeight - MIN_DIST_TOP_START - MIN_DIST_BOTTOM_START) + MIN_DIST_BOTTOM_START;
		double z = std::rand() % (MAX_Z_START - MIN_Z_START) + MIN_Z_START;
		VERTEX_3D_f startingPoint = { DIST_LEFT_OFFSCREEN_START, y, z };
		return startingPoint;
	}

};