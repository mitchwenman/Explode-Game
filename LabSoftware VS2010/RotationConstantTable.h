#pragma once

#include "TrigLookup.h"

class RotationConstantTable
{
private:
	//A copy of the trig lookup table
	TrigLookup* trigLookup;

public:
	RotationConstantTable(int rx, int ry, int rz);
	~RotationConstantTable(void) {};

	//Constant values for public access
	double			xx, xy, xz,
					yx, yy, yz,
					zx, zy, zz;
};

