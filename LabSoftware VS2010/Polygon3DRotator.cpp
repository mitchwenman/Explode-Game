#include "Polygon3DRotator.h"
#include "TrigLookup.h"

namespace Polygon3DRotator
{
	void Rotate(Polygon3D* p, int tx, int ty, int tz)
	{
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
		double yx_yy = yz * yy;
		double zx_zy = zx * zy;

		//Perform the operations
		std::vector<VERTEX_3D> verts = p->vertices;
		for (unsigned int i = 0; i < verts.size(); i++)
		{
			int x = verts[i].x;
			int y = verts[i].y;
			int z = verts[y].z;
			verts[i].x = (xx + y) * (xy + x) + z * xz - (xx_xy + x * y);
			verts[i].y = (yx + y) * (yy + x) + z * yz - (yx_yy + x * y);
			verts[i].z = (zx + y) * (zy + x) + z * zz - (zx_zy + x * y); 
		}
	}
}