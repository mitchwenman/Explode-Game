#include "ExplodedPolygon.h"
#include "World.h"
#include "BoundingBox.h"


class ExplodedPolygonManager
{
private: 

	/******************
	Description: Private constructor for singleton pattern
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: 
	*******************///
	ExplodedPolygonManager() {};

	//Maximum Z value before the poly is cleaned up
	static const int MAX_Z_BEFORE_CLEANUP = 2000;

public:
	//The vector of active polygons
	std::vector<ExplodedPolygon *> explodedPolygons;

	//Returns the singleton instance of ExplodedPolygonManager
	static ExplodedPolygonManager* getSingleton();

	/******************
	Description: Transforms each exploded polygon and draws it to the screen.
	Parameters: bool shoundAnimate: If true, polygons are translated. If false, then not.
	Preconditions: NIL
	Postconditions: NIL
	Returns: void
	*******************/
	void draw(bool shouldAnimate);

	/******************
	Description: Destroys all exploded polygons that are off the screen.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: Polygon pointers will become invalid. Polygon's memory is freed.
	Returns: The number of polygons destroyed.
	*******************/
	int cleanup();

	/******************
	Description: Destroys all polygons stored by the class
	Parameters: NIL
	Preconditions: NIL
	Postconditions: All polygons are destroyed and freed.
	Returns: void
	*******************/
	void reset();

	/******************
	Description: Transforms the first polygon occupying the coordinates into a set of polygon fragments
	Parameters: int x, y: The x,y coordinates.
	Preconditions: NIL
	Postconditions: The polygon stored by PolygonManager3D at the returned index is destroyed.
	Returns: The index of the destroyed polygon, else -1 if none occupied those coordiantes.
	*******************/
	int explodePolygonAtCoords(int x, int y);

	/******************
	Description: Finds the polygon occuping the given coordinates, if any.
	Parameters: int x, y: The x,y coordinates.
	Preconditions: NIL
	Postconditions: NIL
	Returns: The index of the polygon, else -1.
	*******************/
	int polygonAtCoords(int x, int y);

};