#include "RotationConstantTable.h"


RotationConstantTable::RotationConstantTable(int rx, int ry, int rz)
{
	trigLookup = TrigLookup::getSingleton();

	xx = trigLookup->cosLookup(ry) * trigLookup->cosLookup(rz);
	xy = trigLookup->sinLookup(rx) * trigLookup->sinLookup(ry) * trigLookup->cosLookup(rz) -
					trigLookup->cosLookup(rx) * trigLookup->sinLookup(rz);
	xz = trigLookup->cosLookup(rx) * trigLookup->sinLookup(ry) * trigLookup->cosLookup(rz) +
					trigLookup->sinLookup(rx) * trigLookup->sinLookup(rz);
	yx = trigLookup->cosLookup(ry) * trigLookup->sinLookup(rz);
	yy = trigLookup->sinLookup(rx) * trigLookup->sinLookup(ry) * trigLookup->sinLookup(rz) +
					trigLookup->cosLookup(rx) * trigLookup->cosLookup(rz);
	yz = trigLookup->cosLookup(rx) * trigLookup->sinLookup(ry) * trigLookup->sinLookup(rz) -
					trigLookup->sinLookup(rx) * trigLookup->cosLookup(rz);
	zx = -trigLookup->sinLookup(ry);
	zy = trigLookup->sinLookup(rx) * trigLookup->cosLookup(ry);
	zz = trigLookup->cosLookup(rx) * trigLookup->cosLookup(ry);

	xx_xy = xx * xy;
	yx_yy = yx * yy;
	zx_zy = zx * zy;
}

