#include "DDALine.h"
#include <math.h>

DDALine::DDALine(int x1, int y1, int x2, int y2) : GPLine(x1, y1, x2, y2)
{
	initDDALine();
}

DDALine::DDALine(GPLine* gpLine) : GPLine(gpLine->x1, gpLine->y1, gpLine->x2, gpLine->y2) 
{
	this->z1 = gpLine->z1;
	this->z2 = gpLine->z2;
	initDDALine();
	this->c1 = gpLine->c1;
	this->c2 = gpLine->c2;
	
}

void DDALine::initDDALine()
{
	//Find axis of greatest change
	int dx = x2 - x1;
	int dy = y2 - y1;
	int dz = z2 - z1;
	if (abs(dx) > abs(dy)) 
		steps = abs(dx);
	else
		steps = abs(dy);
	//Calculate increments for both axes	
	xInc = dx / (double) steps;
	yInc = dy / (double) steps;
	zInc = dz / (double) steps;
}