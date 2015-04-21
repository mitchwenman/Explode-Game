///////////////////////////////////////////////////////////////////////////////////
// Filename: Polygon3DScaler.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Implements the application of a transformation to a Polygon.
///////////////////////////////////////////////////////////////////////////////////

#include "PolygonTransformation.h"
#include "Polygon3DTranslator.h"
#include "Polygon3DScaler.h"
#include "Polygon3DRotator.h"

void applyRotate(Polygon3D* polygon, Reference3DPolygon * refP);
void applyTranslate(Polygon3D* polygon);
void applyScale(Polygon3D* polygon);

void PolygonTransformation::apply(Polygon3D* polygon, Reference3DPolygon * refP)
{
	switch (transformationType)
	{
	case (SCALE):
		applyScale(polygon);
		break;
	case (ROTATE):
		applyRotate(polygon, refP);
		break;
	case (TRANSLATE):
		applyTranslate(polygon);
		break;
	default:
		break;
	}
}

//Applies a rotate transformation
void PolygonTransformation::applyRotate(Polygon3D* polygon, Reference3DPolygon * refP)
{
	Polygon3DRotator::Rotate(polygon, values.x, values.y, values.z);
	Polygon3DRotator::RotateVertices(&refP->normals, values.x, values.y, values.z);
}

//Applies a translate transformation
void PolygonTransformation::applyTranslate(Polygon3D* polygon)
{
	Polygon3DTranslator::translate(polygon, values.x, values.y, values.z);
}

//Applies a scale transformation
void PolygonTransformation::applyScale(Polygon3D* polygon)
{
	Polygon3DScaler::scale(polygon, values.x, values.y, values.z);
}