#include "Polygon3DRotator.h"
#include "Polygon3DTranslator.h"
#include "TrigLookup.h"
#include "BoundingBox.h"
#include "RotationConstantTable.h"

namespace Polygon3DRotator
{
	void Rotate(Polygon3D* p, int tx, int ty, int tz)
	{
		//Translate to origin
		BoundingBox *b = new BoundingBox(p);
		VERTEX_3D *origCenter = b->calculateCenterPoint();
		Polygon3DTranslator::translate(p, -origCenter->x, -origCenter->y, -origCenter->z);
		//Get constant table
		RotationConstantTable* cTable = new RotationConstantTable(tx, ty, tz);

		//Perform the operations
		for (unsigned int i = 0; i < p->vertices.size(); i++)
		{
			RotateVertex(&p->vertices[i], cTable);
		}
		BoundingBox* newB = new BoundingBox(p);
		VERTEX_3D* newCenter = newB->calculateCenterPoint();
		Polygon3DTranslator::translate(p, origCenter->x - newCenter->x, origCenter->y - newCenter->y, origCenter->z - newCenter->z);
		delete(b);
		delete(newB);
		delete(newCenter);
		delete(origCenter);
	}

	void RotateVertex(VERTEX_3D* vertex, RotationConstantTable* cTable)
	{
		int x = vertex->x;
		int y = vertex->y;
		int z = vertex->z;			
		vertex->x = ceil((cTable->xx + y) * (cTable->xy + x) + z * cTable->xz - (cTable->xx_xy + x * y));
		vertex->y = ceil((cTable->yx + y) * (cTable->yy + x) + z * cTable->yz - (cTable->yx_yy + x * y));
		vertex->z = ceil((cTable->zx + y) * (cTable->zy + x) + z * cTable->zz - (cTable->zx_zy + x * y));  
	}
}