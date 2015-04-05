#ifndef DDALINE_
#define DDALINE_

#include "GPLine.h"

class DDALine : public GPLine
{

public:
	double steps, xInc, yInc, zInc;

	//Creates a DDA line given 2 points
	DDALine(int x1, int y1, int x2, int y2);

	//Creates a DDALine from the GPLine superclass
	DDALine(GPLine* gpLine);

private:

	//Initialise a DDA line with the values required to draw it
	void initDDALine();

};

#endif
