#pragma once

#include "Polygon3D.h"
#include "PolygonDatabase.h"
#include "GraphicsUtil.h"
#include "PolygonTransformation.h"
#include <vector>

/*
 * A namespace for the creation of new polygons by copying from the PolygonDatabase
 * Can create a set of random operations for each created polygon
 */

class Polygon3DFactory
{
private:
	Polygon3DFactory() : scaleCounter(0), speedFactor(1.0) {};

	//Counter incremented each time a scale transformation is created
	//Used in scale factor calculation -- used to decrease scale factor over time
	int scaleCounter;

	//Used to increase the speed of polygons over time by multiplying translation
	//x values by speedfactor
	double speedFactor;

public:
	static const int DIST_LEFT_OFFSCREEN_START = -600; //The distance away from the left of the screen (-X)
													//that the poly should start from

	static const int MIN_DIST_TOP_START = 250; //The minimum distance from the top of the screen
										//that the polygon should start from.

	static const int MIN_DIST_BOTTOM_START = -200; //The minimum distance from the bottom of the screen

	static const int MIN_Z_START = 500; //Minimum z value for polygon to start

	static const int MAX_Z_START = 800; //Max z value

	static const int DEFAULT_X_SPEED = 10;

	static const int Y_TRANSLATE_LIMIT = 4;

	static const int Z_TRANSLATE_LIMIT = 5;


	static Polygon3DFactory* getSingleton();

	//Returns a new copy of a random polygon from the database
	Polygon3D* createRandomPolygonFromDatabase();

	//Creates a random starting point for a new polygon
	VERTEX_3D_f getRandomStartingPoint();

	//Returns a vector of randomly generated PolygonTransformations - scale, translate or rotate
	std::vector<PolygonTransformation> getRandomTransformationSet();

	//Returns a randomised Scale transformation
	PolygonTransformation Polygon3DFactory::getRandomScaleTransformation();

	//Returns a randomised Rotate transformation
	PolygonTransformation Polygon3DFactory::getRandomRotateTransformation();

	//Returns a random translate transformation
	PolygonTransformation Polygon3DFactory::getRandomTranslateTransformation();

	//Resets the factory to it's default state 
	void reset() { scaleCounter = 0; speedFactor = 1.0; }
};