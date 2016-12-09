#ifndef DDALINE_
#define DDALINE_

#include "GPLine.h"

class DDALine : public GPLine
{

public:
	double steps, xInc, yInc, zInc;

	/******************
	Description: DDALine constructor
	Parameters: int x1:	First point x value
				int y1: First point y value
				int x2: Second point x value
				int y2: Second point y value
	Preconditions: NIL
	Postconditions: NIL
	Returns: 
	*******************/
	DDALine(int x1, int y1, int x2, int y2);

	/******************
	Description: DDALine constructor
	Parameters: GPLine* line: The normal line.
	Preconditions: NIL
	Postconditions: NIL
	Returns: 
	*******************/
	DDALine(GPLine* gpLine);

private:

	/******************
	Description: Initialises a DDA line with values required to draw it
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: void
	*******************/
	void initDDALine();

};

#endif
