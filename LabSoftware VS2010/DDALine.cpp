#include "DDALine.h"
#include <math.h>

DDALine::DDALine(int x1, int y1, int x2, int y2)
{
	//Find axis of greatest change
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (abs(dx) > abs(dy)) 
		steps = abs(dx);
	else
		steps = abs(dy);
	//Calculate increments for both axes	
	xInc = dx / (double) steps;
	yInc = dy / (double) steps;
	//Place in struct
	steps = steps;
	xInc = xInc;
	yInc = yInc;
}