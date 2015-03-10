#ifndef DDALINE_
#define DDALINE_

#include "GPLine.h"

class DDALine : public GPLine
{

public:
	double steps, xInc, yInc;

	DDALine(int x1, int y1, int x2, int y2);
	DDALine(GPLine* gpLine);

private:
	void initDDALine();

};

#endif
