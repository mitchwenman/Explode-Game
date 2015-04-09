#include "Polygon3DFactory.h"
#include "GraphicsSettings.h"
#include <stdlib.h> //Rand

static Polygon3DFactory* _instance;

PolygonTransformation getRandomScaleTransformation();		//Creates a randomised scale operation
PolygonTransformation getRandomRotateTransformation();		//Creates a randomised rotate operation
PolygonTransformation getRandomTranslateTransformation();	//Creates a random translate operation

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
		RGBColour colcopy = { original.c->red, original.c->green, original.c->blue };
		VERTEX_3D vcopy = { original.x, original.y, original.z, &colcopy };
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
	int shouldscale = std::rand() % 1;
	int shouldRotate = std::rand() % 4;
	if (shouldscale)
		transformations.push_back(getRandomScaleTransformation());
	if (shouldRotate > 0) //75% rotation chance
		transformations.push_back(getRandomRotateTransformation());
	return transformations;
}

PolygonTransformation getRandomScaleTransformation()
{
	PolygonTransformation scale;
	scale.transformationType = SCALE;
	VERTEX_3D_f scalefactors = { 1.0, 1.0, 1.0 };
	scale.values = scalefactors;
	return scale;
}

PolygonTransformation getRandomRotateTransformation()
{
	PolygonTransformation rotate;
	VERTEX_3D_f rotateFactors = { 0, 0, 0 };
	rotate.transformationType = ROTATE;
	rotate.values = rotateFactors;
	return rotate;
}

PolygonTransformation getRandomTranslateTransformation()
{
	PolygonTransformation translate;
	VERTEX_3D_f translateFactors = { 10, 0, 0 };
	translate.transformationType = TRANSLATE;
	translate.values = translateFactors;
	return translate;
}