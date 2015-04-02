#include "Reference3DPolygon.h"

Reference3DPolygon::Reference3DPolygon(Polygon3D* p) : sx(0), sy(0), sz(0), tx(0), ty(0), tz(0), rx(0), ry(0), rz(0)
{
	this->originalPoly = new Polygon3D(*p);
}