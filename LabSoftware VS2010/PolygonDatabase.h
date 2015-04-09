#pragma once

/*
 * A class for storing objects from VJS files.
 * Avoids having to read from VJS file each time a new polygon is needed
 */

#include "Polygon3D.h"

#include <vector>

class PolygonDatabase
{
private:
	//Default constructor
	PolygonDatabase() {};

	


public:

	//Returns the polygon database singleton
	static PolygonDatabase* getSingleton();

	//Loads a polygon from a VJS file into the database
	//Returns whether it was loaded successfully
	bool loadPolygonAtPath(std::string path);

	//The polygon database
	std::vector<Polygon3D *> polygons;

};