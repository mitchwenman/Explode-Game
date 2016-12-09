#pragma once

#include "GraphicsUtil.h"
#include "Polygon3D.h"
#include "Reference3DPolygon.h"

typedef enum  { TRANSLATE, SCALE, ROTATE } TransformationType;

class PolygonTransformation
{	
private:
	/******************
	Description:Applies a rotate operation to the given poly and reference polygon.
	Parameters: Polygon3D* polygon: The polygon to be transformed.
				Reference3DPolygon refP: The reference polygon whose normals are modified.
	Preconditions: Input param(s) not null.
					refP->polygon = polygon
	Postconditions: Polygon vertices and reference polygon normals are modified.
	Returns:  void
	*******************/
	void applyRotate(Polygon3D* polygon, Reference3DPolygon * refP);

	/******************
	Description:Applies a translate operation to the given poly.
	Parameters: Polygon3D* polygon: The polygon to be transformed.
	Preconditions: Input param(s) not null.
	Postconditions: Polygon vertices are modified.
	Returns:  void
	*******************/
	void applyTranslate(Polygon3D* polygon);

	/******************
	Description:Applies a scale operation to the given poly.
	Parameters: Polygon3D* polygon: The polygon to be transformed.
	Preconditions: Input param(s) not null.
	Postconditions: Polygon vertices are modified.
	Returns:  void
	*******************/
	void applyScale(Polygon3D* polygon);

public:
	//Defines the type of transformation
	//Translate, scale or rotate
	TransformationType transformationType;

	//The values of the transformation
	VERTEX_3D_f values;

	/******************
	Description: Applies this transformation to the given polygon and reference polygon normals (if rotating)
	Parameters: Polygon3D* polygon: The polygon to be transformed.
				Reference3DPolygon refP: The reference polygon whose normals are modified if rotating.
	Preconditions: Input param(s) not null.
					refP->polygon = polygon
	Postconditions: Polygon vertices and reference polygon normals are modified.
	Returns:  void
	*******************/
	void apply(Polygon3D *polygon, Reference3DPolygon * refP);

};