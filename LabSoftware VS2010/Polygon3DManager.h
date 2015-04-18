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

	//Private constructor for singleton pattern
	Polygon3DManager() : polyCreationInterval(DEF_CREATION_INTERVAL), firstPoly(true) {};

	//Used to create a polygon straight away on startup or reset
	bool firstPoly;

public:
	//Gets the singleton instance of Polygon3DManager
	static Polygon3DManager* getSingleton();

	//Returns the polygon3ds vector
	std::vector<Polygon3D*> getPolygon3Ds() { return polygon3ds; }

	//Returns the reference polygon vector
	std::vector<Reference3DPolygon *> getReferencePolygons() { return referencePolygons; }

	//Draws the current 3d polygons to the frame buffer
	void animate(bool shouldAnimate);

	//Removes the polygon, reference polygon and transformations
	//for a given index
	void removePolygonAtIndex(int i);

	//Removes any polygons not on the screen anymore
	//Returns the number of polygons removed
	int cleanup();

	//Resets the manager to its initial state with no polygons
	void reset();

	//Adds a new polygon to the vector if is ready to
	//Polygons will be added to the vector more regularly as time progresses
	//Returns the newly created polygon or NULL if one wasn't created
	Polygon3D* addNewPolygonIfReady();

	//Applys a set of transformations to the polygon
	void applyTransformations(Polygon3D* polygon, Reference3DPolygon* refP, std::vector<PolygonTransformation> transformations);
};