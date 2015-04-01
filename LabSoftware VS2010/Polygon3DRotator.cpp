#include "Polygon3DRotator.h"
#include "Polygon3DTranslator.h"
#include "TrigLookup.h"
#include "BoundingBox.h"

namespace Polygon3DRotator
{
	void Rotate(Polygon3D* p, int tx, int ty, int tz)
	{
		//Translate to origin
		BoundingBox *b = new BoundingBox(p);
		VERTEX_3D *origCenter = b->calculateCenterPoint();
		Polygon3DTranslator::translate(p, -origCenter->x, -origCenter->y, -origCenter->z);
		//Get lookup singeton
		TrigLookup* l = TrigLookup::getSingleton();
		
		//Calculate constants
		double xx = l->cosLookup(ty) * l->cosLookup(tz);
		double xy = l->sinLookup(tx) * l->sinLookup(ty) * l->cosLookup(tz) -
						l->cosLookup(tx) * l->sinLookup(tz);
		double xz = l->cosLookup(tx) * l->sinLookup(ty) * l->cosLookup(tz) +
						l->sinLookup(tx) * l->sinLookup(tz);
		double yx = l->cosLookup(ty) * l->sinLookup(tz);
		double yy = l->sinLookup(tx) * l->sinLookup(ty) * l->sinLookup(tz) +
						l->cosLookup(tx) * l->cosLookup(tz);
		double yz = l->cosLookup(tx) * l->sinLookup(ty) * l->sinLookup(tz) -
						l->sinLookup(tx) * l->cosLookup(tz);
		double zx = -l->sinLookup(ty);
		double zy = l->sinLookup(tx) * l->cosLookup(ty);
		double zz = l->cosLookup(tx) * l->cosLookup(ty);

		//Object kept intact - constants
		double xx_xy = xx * xy;
		double yx_yy = yx * yy;
		double zx_zy = zx * zy;

		//Perform the operations
		for (unsigned int i = 0; i < p->vertices.size(); i++)
		{
			int x = p->vertices[i].x;
			int y = p->vertices[i].y;
			int z = p->vertices[i].z;			
			p->vertices[i].x = floor((xx + y) * (xy + x) + z * xz - (xx_xy + x * y));
			p->vertices[i].y = floor((yx + y) * (yy + x) + z * yz - (yx_yy + x * y));
			p->vertices[i].z = floor((zx + y) * (zy + x) + z * zz - (zx_zy + x * y));   
		}
		BoundingBox* newB = new BoundingBox(p);
		VERTEX_3D* newCenter = newB->calculateCenterPoint();
		Polygon3DTranslator::translate(p, origCenter->x - newCenter->x, origCenter->y - newCenter->y, origCenter->z - newCenter->z);
		delete(b);
		delete(newB);
		delete(newCenter);
		delete(origCenter);
	}
}