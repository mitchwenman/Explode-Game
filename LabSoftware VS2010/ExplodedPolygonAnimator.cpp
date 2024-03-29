///////////////////////////////////////////////////////////////////////////////////
// Filename: ExplodedPolygonAnimator.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Animates an Exploded Polygon object by moving it and drawing it.
///////////////////////////////////////////////////////////////////////////////////

//=======INCLUDES=========//
#include "ExplodedPolygonAnimator.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DTranslator.h"
#include "GraphicsSettings.h"


//=========FUNCTIONS========//

void ExplodedPolygonAnimator::animateExplodedPolygon(ExplodedPolygon* poly)
{	
	Polygon3DTranslator::translate(poly, 
						DEFAULT_SPEED * poly->trajectory.x,
						DEFAULT_SPEED * poly->trajectory.y,
						DEFAULT_SPEED * poly->trajectory.z);
	PolygonDrawer3D::draw(poly);
	

	
}