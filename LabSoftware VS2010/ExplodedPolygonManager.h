#include "ExplodedPolygon.h"
#include "World.h"
#include "BoundingBox.h"


class ExplodedPolygonManager
{
private: 

	//Private constructor for the ExplodedPolygonManager
	ExplodedPolygonManager() {};

public:
	//The vector of active polygons
	std::vector<ExplodedPolygon *> explodedPolygons;

	//Returns the singleton instance of ExplodedPolygonManager
	ExplodedPolygonManager* getSingleton();

	//Animates and draws the current exploded polygons to the framebuffer
	void draw();

	//Cleanup method destroys all exploded polygons that are off the screen
	//Returns the number of polygons it cleaned up 
	int cleanup();

	//Checks the coordinates and explodes the 
	//first polygon it finds. Removes original
	//poly from the world
	//Returns: the index of the world polygon it exploded, else
	//returns -1
	int explodePolygonAtCoords(int x, int y);

	//Retruns the index of the polygon at the coords given
	//Otherwise returns -1
	int polygonAtCoords(int x, int y);

};