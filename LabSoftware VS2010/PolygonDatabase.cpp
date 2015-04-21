///////////////////////////////////////////////////////////////////////////////////
// Filename: PolygonDatabase.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Class for managing the storage and loading of 3D polygons into the game.
///////////////////////////////////////////////////////////////////////////////////


#include "PolygonDatabase.h"
#include "VJSReader.h"

static PolygonDatabase* _instance;

PolygonDatabase* PolygonDatabase::getSingleton()
{
	if (_instance == NULL)
	{
		_instance = new PolygonDatabase();
	}
	return _instance;
}

bool PolygonDatabase::loadPolygonAtPath(std::string path)
{
	Polygon3D *newPoly = VJSReader::read(path);
	if (newPoly)
	{
		polygons.push_back(newPoly);
		return true; 
	}
	return false;
}