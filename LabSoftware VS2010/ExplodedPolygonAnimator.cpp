#include "ExplodedPolygonAnimator.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DTranslator.h"

void ExplodedPolygonAnimator::animateExplodedPolygon(ExplodedPolygon* poly)
{
	
	PolygonDrawer3D::draw(poly);
	Polygon3DTranslator::translate(poly, 
		DEFAULT_SPEED * poly->trajectory.x,
		DEFAULT_SPEED * poly->trajectory.y,
		DEFAULT_SPEED * poly->trajectory.z);

	
}