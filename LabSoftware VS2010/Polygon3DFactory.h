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

	/******************
	Description: Creates if needed and returns singleton object
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: The polygon factory instance.
	*******************///
	static Polygon3DFactory* getSingleton();

	/******************
	Description: Creates a copy of a random poly in the database.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: The copied polygon
	*******************///
	Polygon3D* createRandomPolygonFromDatabase();

	/******************
	Description: Creates a random starting point for a polygon. X value is constant. Y/Z values will differ within a range.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: x, y, z coordinates
	*******************///
	VERTEX_3D_f getRandomStartingPoint();

	/******************
	Description: Creates a randomly generated translate and rotate transformation
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: The rotate/translate operations in a vector.
	*******************///
	std::vector<PolygonTransformation> getRandomTransformationSet();

	/******************
	Description: Creates a randomised scale transformation.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  a randomised scale transformation
	*******************///
	PolygonTransformation Polygon3DFactory::getRandomScaleTransformation();

	/******************
	Description: Creates a randomised rotate transformation.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  a randomised rotate transformation
	*******************///
	PolygonTransformation Polygon3DFactory::getRandomRotateTransformation();
	
	/******************
	Description: Creates a translate scale transformation.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  a randomised translate transformation with a positive X value
	*******************///
	PolygonTransformation Polygon3DFactory::getRandomTranslateTransformation();

	//Resets the factory to it's default state 
	void reset() { scaleCounter = 0; speedFactor = 1.0; }
};