#include "Polygon3DTranslator.h"

namespace Polygon3DTranslator
{
	void translate(Polygon3D* p, int dx, int dy, int dz)
	{
		int size = p->vertices.size();
		for (int i = 0; i < size; i++)
		{
			translatePoint(&p->vertices[i], dx, dy, dz);
		}
	}

	void translatePoint(VERTEX_3D* p, int dx, int dy, int dz)
	{
		p->x += dx;
		p->y += dy;
		p->z += dz;
	}
}