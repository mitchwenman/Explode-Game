#pragma once

#include "Polygon3D.h"
#include "PolygonTransformation.h"
#include "Reference3DPolygon.h"

#include <vector>

#define DEF_CREATION_INTERVAL RAND_MAX/200

class Polygon3DManager
{
private:
	//The vector of currently active polygons
	std::vector<Polygon3D *> polygon3ds;

	//The parallel vector of reference polygons
	std::vector<Reference3DPolygon *> referencePolygons;

	//The vector (parallel to polygon vector) that contains the transformations
	//to be applied prior to drawing the polygon
	std::vector<std::vector<PolygonTransformation>> transformations;

	//Counter used to determine when to create a new polygon
	int polyCreationInterval;

	/******************
	Description: Private constructor for singleton pattern
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: 
	*******************///
	Polygon3DManager() : polyCreationInterval(DEF_CREATION_INTERVAL), firstPoly(true) {};

	//Used to create a polygon straight away on startup or reset
	bool firstPoly;

public:
	/******************
	Description: Creates if needed and returns singleton instance.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: The singleton instance of polygon manager.
	*******************///
	static Polygon3DManager* getSingleton();

	//Returns the polygon3ds vector
	std::vector<Polygon3D*> getPolygon3Ds() { return polygon3ds; }

	//Returns the reference polygon vector
	std::vector<Reference3DPolygon *> getReferencePolygons() { return referencePolygons; }

	/******************
	Description: Draws all polygons to the buffer, animating if necessary
	Parameters: bool shouldAnimate: Whether or not the polygon's transformations should be applied before drawing.
	Preconditions: NIL
	Postconditions: The vertices of each polygon will be changed if shouldAnimate == true
	Returns:  void
	*******************///
	void animate(bool shouldAnimate);

	/******************
	Description: Removes and destroys the polygon at position i.
	Parameters: int i: The index of the to be destroyed polygon.
	Preconditions: NIL
	Postconditions: The polygon will be freed/destroyed.
	Returns:  void
	*******************///
	void removePolygonAtIndex(int i);

	/******************
	Description: Destroys all polygons not on the screen anymore.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: Polygons not on the screen anymore will be destroyed/freed.IL
	Returns:  void
	*******************///
	int cleanup();

	/******************
	Description: Resets the manager to it's initial state with no polygons.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: All polygons destroyed/freeed
	Returns:  void
	*******************///
	void reset();

	/******************
	Description: Creates a new polygon at random (but controlled by a limit). Repetitve calls to this function will cause polygon creation interval to decrease.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: Repetitve calls to this function will cause polygon creation interval to decrease.
	Returns:  The polygon if created, else null.
	*******************///
	Polygon3D* addNewPolygonIfReady();

	/******************
	Description: Applies a set of transformations to a polygon.
	Parameters: Polygon3D* polygon: The polygon to be transformed
				Reference3DPolygon: The reference polygon containing the surface normals.
				vector<PolygonTransformation> : THe transformations to be applied to the polygon
	Preconditions: NIL
	Postconditions: Vertices of polygon will be modified by transformations.
	Returns:  void
	*******************///
	void applyTransformations(Polygon3D* polygon, Reference3DPolygon* refP, std::vector<PolygonTransformation> transformations);
};