#include "SurfaceNormal.h"
#include "Polygon3DTranslator.h"
#include <math.h>

VERTEX_3D_f* SurfaceNormal::calculateSurfaceNormal(VERTEX_3D v1, VERTEX_3D v2, VERTEX_3D v3)
{
	//Translate each point to origin
	//VERTEX_3D p1 = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	//VERTEX_3D p2 = { 0, 0, 0 };
	//VERTEX_3D p3 = { v3.x - v2.x, v3.y - v2.y, v3.z - v2.z };
	
	//Create vectorsv
	VERTEX_3D_f vectorA = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
	VERTEX_3D_f vectorB = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };

	//Normalise to unit length
	double lengthA = sqrt( (double)(vectorA.x * vectorA.x + vectorA.y * vectorA.y + vectorA.z * vectorA.z) );
	vectorA.x /= lengthA; vectorA.y /= lengthA; vectorA.z /= lengthA;
	double lengthB = sqrt( (double)(vectorB.x * vectorB.x + vectorB.y * vectorB.y + vectorB.z * vectorB.z) );
	vectorB.x /= lengthB; vectorB.y /= lengthB; vectorB.z /= lengthB;

	//Cross product
	VERTEX_3D_f *normal = new VERTEX_3D_f;
	normal->x = vectorA.y * vectorB.z - vectorA.z * vectorB.y;
	normal->y = -(vectorA.x * vectorB.z - vectorA.z * vectorB.x);
	normal->z = vectorA.x * vectorB.y - vectorA.y * vectorB.x;


	return normal;
}