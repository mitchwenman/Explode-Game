#include "Polygon3DFactory.h"
#include "GraphicsSettings.h"
#include <stdlib.h> //Rand

namespace Polygon3DFactory
{
	//Returns a new copy of a random polygon from the database
	Polygon3D* createRandomPolygonFromDatabase()
	{
		Polygon3D* newPoly = new Polygon3D();
		Polygon3D* blueprint;
		PolygonDatabase *db = PolygonDatabase::getSingleton();
		//Select random polygon to recreate
		unsigned int size = db->polygons.size();
		int randIndex;
		while (true)
		{
			randIndex = std::rand() % size;
			blueprint = db->polygons[randIndex];
			if (blueprint)
				break;
		}
		//For each vertex copy values and create new colour pointer
		for (unsigned int i = 0; i < blueprint->vertices.size(); i++)
		{
			VERTEX_3D original = blueprint->vertices[i];
			RGBColour colcopy = { original.c->red, original.c->green, original.c->blue };
			VERTEX_3D vcopy = { original.x, original.y, original.z, &colcopy };
			newPoly->vertices.push_back(vcopy);
		}

		//Simply copy the polygon face definitions
		newPoly->polygons = blueprint->polygons;

		return newPoly;
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