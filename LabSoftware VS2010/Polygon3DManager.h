#pragma once

#include "Polygon3D.h"
#include "Polygon3DFactory.h"
#include "PolygonTransformation.h"

#include <vector>

class Polygon3DManager
{
private:
	//The vector of currently active polygons
	std::vector<Polygon3D *> polygon3ds;

	//The vector (parallel to polygon vector) that contains the transformations
	//to be applied prior to drawing the polygon
	std::vector<std::vector<PolygonTransformation>> transformations;

	//Private constructor for singleton pattern
	Polygon3DManager() {};

public:
	//Gets the singleton instance of Polygon3DManager
	Polygon3DManager* getSingleton();

	//Returns the polygon3ds vector
	std::vector<Polygon3D*> getPolygon3Ds() { return polygon3ds; }

	//Draws the current 3d polygons to the frame buffer
	void animate();

	//Removes any polygons not on the screen anymore
	//Returns the number of polygons removed
	int cleanup();

	//Adds a new polygon to the vector if is ready to
	//Polygons will be added to the vector more regularly as time progresses
	//Returns the newly created polygon or NULL if one wasn't created
	Polygon3D* addNewPolygonIfReady();

	//Applys a set of transformations to the polygon
	void applyTransformations(Polygon3D* polygon, std::vector<PolygonTransformation> transformations);
};