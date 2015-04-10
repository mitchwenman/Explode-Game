#include "Polygon3DFactory.h"
#include "GraphicsSettings.h"
#include <stdlib.h> //Rand

static Polygon3DFactory* _instance;

Polygon3DFactory* Polygon3DFactory::getSingleton()
{
	if (!_instance)
		_instance = new Polygon3DFactory();
	return _instance;
}

Polygon3D* Polygon3DFactory::createRandomPolygonFromDatabase()
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
		RGBColour *colcopy = new RGBColour();
		colcopy->red = original.c->red;
		colcopy->green = original.c->green;
		colcopy->blue = original.c->blue;
		VERTEX_3D vcopy = { original.x, original.y, original.z, colcopy };
		newPoly->vertices.push_back(vcopy);
	}

	//Simply copy the polygon face definitions
	newPoly->polygons = blueprint->polygons;
	return newPoly;
}

VERTEX_3D_f Polygon3DFactory::getRandomStartingPoint()
{
	GraphicsSettings* gsettings = GraphicsSettings::getGraphicsSettings();
	int frameHeight = gsettings->getFrameHeight();
	double y = std::rand() % (frameHeight - MIN_DIST_TOP_START - MIN_DIST_BOTTOM_START) + MIN_DIST_BOTTOM_START;
	double z = std::rand() % (MAX_Z_START - MIN_Z_START) + MIN_Z_START;
	VERTEX_3D_f startingPoint = { DIST_LEFT_OFFSCREEN_START, y, z };
	return startingPoint;
}

std::vector<PolygonTransformation> Polygon3DFactory::getRandomTransformationSet() //XXX
{
	std::vector<PolygonTransformation> transformations;
	transformations.push_back(getRandomTranslateTransformation());
	transformations.push_back(getRandomRotateTransformation());
	return transformations;
}

PolygonTransformation Polygon3DFactory::getRandomScaleTransformation()
{
	PolygonTransformation scale;
	scale.transformationType = SCALE;
	double x = 1.0 - ((double) std::rand() / RAND_MAX) / 2;
	double y = 1.0 - ((double)std::rand() / RAND_MAX) / 2;
	double z = 1.0 - ((double)std::rand() / RAND_MAX) / 2;
	VERTEX_3D_f scalefactors = { x, y, z };
	scale.values = scalefactors;
	return scale;
}

PolygonTransformation Polygon3DFactory::getRandomRotateTransformation()
{
	PolygonTransformation rotate;
	VERTEX_3D_f rotateFactors = { std::rand() % 15, std::rand() % 15, std::rand() % 15 };
	rotate.transformationType = ROTATE;
	rotate.values = rotateFactors;
	return rotate;
}

PolygonTransformation Polygon3DFactory::getRandomTranslateTransformation()
{
	PolygonTransformation translate;
	int y = std::rand() % Y_TRANSLATE_LIMIT;
	int z = std::rand() % Z_TRANSLATE_LIMIT;
	VERTEX_3D_f translateFactors = { Polygon3DFactory::DEFAULT_X_SPEED * speedFactor , y, z };
	speedFactor += 0.75;
	translate.transformationType = TRANSLATE;
	translate.values = translateFactors;
	return translate;
}