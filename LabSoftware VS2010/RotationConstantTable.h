#pragma once

#include "TrigLookup.h"

class RotationConstantTable
{
private:
	//A copy of the trig lookup table
	TrigLookup* trigLookup;

public:

	/******************
	Description:Creates a lookup table for a rotation operation.Limits repeated math operations.
	Parameters: int rx, ry, rz: The rotation values for the x, y, z values in degrees.
	Preconditions: NIL
	Postconditions: NIL
	Returns:  
	*******************/
	RotationConstantTable(int rx, int ry, int rz);

	~RotationConstantTable(void) {};

	//Constant values for public access
	double	xx, xy, xz,
			yx, yy, yz,
			zx, zy, zz;

	//Constant values - because object kept intact
	double	xx_xy,
			yx_yy,
			zx_zy;
};

