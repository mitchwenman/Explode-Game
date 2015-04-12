#include "ExplodedPolygonAnimator.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DTranslator.h"
#include "GraphicsSettings.h"

void ExplodedPolygonAnimator::animateExplodedPolygon(ExplodedPolygon* poly)
{
	if (!GraphicsSettings::getGraphicsSettings()->isSecondFrame())
		Polygon3DTranslator::translate(poly, 
							DEFAULT_SPEED * poly->trajectory.x,
							DEFAULT_SPEED * poly->trajectory.y,
							DEFAULT_SPEED * poly->trajectory.z);
	PolygonDrawer3D::draw(poly);
	

	
}