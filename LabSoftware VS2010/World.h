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

	

public:

	std::vector<Polygon3D *> polygon3ds;
	std::vector<Polygon2D *> polygon2ds;

	//A vector of polygons pre-all transformations 
	//Used to combat loss of precision in rotate operations
	std::vector<Reference3DPolygon *> originalPolygons;

	/******************
	Description:Creates if needed and returns singleton object
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  World singleton
	*******************/
	static World* getSingleton();

	/******************
	Description:Translates the given polygon such that its center is at the given x, y, z values in the world.
	Parameters: Polygon3D* p: The polygon to be translated and inserted.
				int x, y, z: The position in the world that p will be inserted.
	Preconditions: NIL
	Postconditions: p's vertices will be modified if translated.
	Returns:  The index where the polygon was inserted into the vector.
	*******************/
	int insert3DPoly(Polygon3D* p, int x, int y, int z);

	/******************
	Description:Destroys the polygon at position i in the 3D polygon vector
	Parameters: int i: The position of the polygon to be destroyed.
	Preconditions: i < polygons.size()
	Postconditions: The polygon is destroyed and it's memory freed
	Returns:  void
	*******************/
	void remove3DPolyAtPosition(int i);

	/******************
	Description:Translates a given polygon into the world.
	Parameters: Polygon2D* p: THe polygon to be inserted.
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void insert2DPoly(Polygon2D* p);

	/******************
	Description:Draws all 3d and 2d polygons.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void drawWorld();

	/******************
	Description:Translates the polygon at index i by the desired values.
	Parameters: int i: THe index of the polygon.
				int dx, dy, dz: The x, y, z translation values.
	Preconditions: i < polygons.size()
	Postconditions: NIL
	Returns:  void
	*******************/
	void translate3DPolyAtIndex(int i, int dx, int dy, int dz);

	/******************
	Description:Rotates the polygon at index i by the desired values.
	Parameters: int i: THe index of the polygon.
				int dx, dy, dz: The x, y, z rotation values.
	Preconditions: i < polygons.size()
	Postconditions: NIL
	Returns:  void
	*******************/
	void rotate3DPolyAtIndex(int i, int dx, int dy, int dz);

	/******************
	Description:Scales the polygon at index i by the desired values.
	Parameters: int i: THe index of the polygon.
				int sx, sy, sz: The x, y, z scaling values.
	Preconditions: i < polygons.size()
	Postconditions: NIL
	Returns:  void
	*******************/
	void scale3DPolyAtIndex(int i, double sx, double sy, double sz);


};


#endif