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