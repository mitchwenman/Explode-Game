#ifndef BOUNDINGBOX_
#define BOUNDINGBOX_

#include "GraphicsUtil.h"
#include "Polygon3D.h"

class BoundingBox
{
private:
	Polygon3D* p;

public:
	
	/******************
	Description: Constructor
	Parameters: Polygon3D* p: THe polygon for which the box will describe.
	Preconditions: Input params are not NULL.
	Postconditions: NIL
	*******************/
	BoundingBox(Polygon3D* p) : p(p) {};
	~BoundingBox(void);

	/******************
	Description: Calculates the center point of the box
	Parameters: NIL
	Preconditions: this->p is not null.
	Postconditions: Returned value must be deleted
	Returns: The center vector of the box.
	*******************/
	VERTEX_3D* calculateCenterPoint();

	/******************
	Description: Finds the maximum X value of the polygon.
	Parameters: NIL
	Preconditions: this->p is not null.
	Postconditions: NIL
	Returns: The maximum X value of the polygon.
	*******************/
	int findMaxX();

	/******************
	Description: Finds the minimum Y value of the polygon.
	Parameters: NIL
	Preconditions: this->p is not null.
	Postconditions: NIL
	Returns: The minimum Y value of the polygon.
	*******************/
	int findMinX();
	
	/******************
	Description: Finds the maximum Y value of the polygon.
	Parameters: NIL
	Preconditions: this->p is not null.
	Postconditions: NIL
	Returns: The maximum Y value of the polygon.
	*******************/
	int findMaxY();

	/******************
	Description: Finds the minimum Y value of the polygon.
	Parameters: NIL
	Preconditions: this->p is not null.
	Postconditions: NIL
	Returns: The minimum Y value of the polygon.
	*******************/
	int findMinY();

	/******************
	Description: Finds the maximum Z value of the polygon.
	Parameters: NIL
	Preconditions: this->p is not null.
	Postconditions: NIL
	Returns: The maximum Z value of the polygon.
	*******************/
	int findMaxZ();

	/******************
	Description: Finds the minimum Z value of the polygon.
	Parameters: NIL
	Preconditions: this->p is not null.
	Postconditions: NIL
	Returns: The minimum Z value of the polygon.
	*******************/
	int findMinZ();
};

#endif