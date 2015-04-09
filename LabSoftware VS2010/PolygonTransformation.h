#pragma once

#include "GraphicsUtil.h"

typedef enum  { TRANSLATE, SCALE, ROTATE } TransformationType;

class PolygonTransformation
{	

public:
	TransformationType transformationType;

	VERTEX_3D_f values;

};