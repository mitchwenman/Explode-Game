#pragma once

#include "GraphicsUtil.h"
#include "Polygon3D.h"
#include "Reference3DPolygon.h"

typedef enum  { TRANSLATE, SCALE, ROTATE } TransformationType;

class PolygonTransformation
{	
private:
	//Applies a rotate transformation
	void applyRotate(Polygon3D* polygon, Reference3DPolygon * refP);

	//Applies a translate transformation
	void applyTranslate(Polygon3D* polygon);

	//Applies a scale transformation
	void applyScale(Polygon3D* polygon);

public:
	//Defines the type of transformation
	//Translate, scale or rotate
	TransformationType transformationType;

	//The values of the transformation
	VERTEX_3D_f values;

	//Applies the transformation to a given polygon
	void apply(Polygon3D *polygon, Reference3DPolygon * refP);

};