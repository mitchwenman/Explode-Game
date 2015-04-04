#ifndef WORLD_
#define WORLD_

#include "Polygon3D.h"
#include "Polygon2D.h"
#include "3DPolygonDrawer.h"
#include "Reference3DPolygon.h"

#include <vector>

class World
{

	static const int N_ROTATES_BEFORE_REDRAW = 50;

private:
	//Constructor
	World() { };

	//A vector of polygons pre-all transformations 
	//Used to combat loss of precision in rotate operations
	std::vector<Reference3DPolygon *> originalPolygons;

public:

	std::vector<Polygon3D *> polygon3ds;
	std::vector<Polygon2D *> polygon2ds;

	//Creates if needed and returns the World singleton object
	static World* getSingleton();

	//Translates the polygon such that the centre of the polygon is
	//at the given coordinates and adds it to the 3D poly vector
	void insert3DPolyAtPosition(Polygon3D* p, int x, int y, int z);

	//Adds the polygon to the 2D poly vector
	void insert2DPoly(Polygon2D* p);

	//Draws the 2D and 3D to the frame buffer stored in GraphicsSettings
	void drawWorld();

	//Translates the polygon at the index i in polygon3ds
	void translate3DPolyAtIndex(int i, int dx, int dy, int dz);

	//Rotates the polygon at the index i in polygon3ds
	void rotate3DPolyAtIndex(int i, int dx, int dy, int dz);

	//Scales the polygon at the index i in polygon3ds
	void scale3DPolyAtIndex(int i, double sx, double sy, double sz);


};


#endif