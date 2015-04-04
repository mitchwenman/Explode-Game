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
		RotateVertices(&p->vertices, cTable);
		BoundingBox* newB = new BoundingBox(p);
		VERTEX_3D* newCenter = newB->calculateCenterPoint();
		Polygon3DTranslator::translate(p, origCenter->x - newCenter->x, origCenter->y - newCenter->y, origCenter->z - newCenter->z);
		delete(b);
		delete(newB);
		delete(newCenter);
		delete(origCenter);
	}

	void RotateVertices(std::vector<VERTEX_3D>* vertices, RotationConstantTable* cTable)
	{
		for (unsigned int i = 0; i < vertices->size(); i++)
		{
			RotateVertex(&vertices->at(i), cTable);
		}
	}

	void RotateVertices(std::vector<VERTEX_3D_f>* vertices, int rx, int ry, int rz)
	{
		RotationConstantTable* cTable = new RotationConstantTable(rx, ry, rz);
		for (unsigned int i = 0; i < vertices->size(); i++)
		{
			RotateVertex(&vertices->at(i), cTable);
		}
	}

	void RotateVertex(VERTEX_3D* vertex, RotationConstantTable* cTable)
	{
		double x = vertex->x;
		double y = vertex->y;
		double z = vertex->z;			
		vertex->x = (cTable->xx + y) * (cTable->xy + x) + z * cTable->xz - (cTable->xx_xy + x * y);
		vertex->y = (cTable->yx + y) * (cTable->yy + x) + z * cTable->yz - (cTable->yx_yy + x * y);
		vertex->z = (cTable->zx + y) * (cTable->zy + x) + z * cTable->zz - (cTable->zx_zy + x * y);  
	}

	void RotateVertex(VERTEX_3D_f* vertex, RotationConstantTable* cTable)
	{
		double x = vertex->x;
		double y = vertex->y;
		double z = vertex->z;			
		vertex->x = (cTable->xx + y) * (cTable->xy + x) + z * cTable->xz - (cTable->xx_xy + x * y);
		vertex->y = (cTable->yx + y) * (cTable->yy + x) + z * cTable->yz - (cTable->yx_yy + x * y);
		vertex->z = (cTable->zx + y) * (cTable->zy + x) + z * cTable->zz - (cTable->zx_zy + x * y);  
	}
}