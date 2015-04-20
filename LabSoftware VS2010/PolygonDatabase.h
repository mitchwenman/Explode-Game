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
	/******************
	Description: Private constructor for singleton pattern
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  
	*******************/
	PolygonDatabase() {};

	


public:

	/******************
	Description: Creates if needed and returns the polygon database singleton.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	static PolygonDatabase* getSingleton();

	/******************
	Description: Loads a VJS polygon into the database
	Parameters: string path: The path to the VJS file.
	Preconditions: Input params not null.
	Postconditions: The polygon is added to the database vector.
	Returns:  void
	*******************/
	bool loadPolygonAtPath(std::string path);

	//The polygon database
	std::vector<Polygon3D *> polygons;

};