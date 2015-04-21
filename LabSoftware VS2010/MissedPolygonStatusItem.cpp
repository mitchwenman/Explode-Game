///////////////////////////////////////////////////////////////////////////////////
// Filename: MissedPolygonStatusItem.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Implements IStatusItem. Draws the number of missed polygons to the display
///////////////////////////////////////////////////////////////////////////////////

#include "MissedPolygonStatusItem.h"
#include "Game.h"
#include "GraphicsUtil.h"
#include "GraphicsSettings.h"
#include "libs/glut.h"
#include <sstream>

void MissedPolygonStatusItem::draw()
{
	Game* game = Game::getSingleton();
	int numMissedPolygons =  game->getNumberOfMissedPolygons();
	int maxMissedPolygons = game->MAX_MISSED_POLYGONS;
	GraphicsSettings *gset = GraphicsSettings::getGraphicsSettings();
	std::stringstream stream;
	stream << "Missed: " << numMissedPolygons << " / " << maxMissedPolygons;
	if (numMissedPolygons == maxMissedPolygons)
		glColor3f(1.0, 0.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1.0);
	GraphicsUtil::drawString(GLUT_BITMAP_TIMES_ROMAN_24, stream.str(),
		gset->getFrameWidth() - MPSI_XOFFSET_RIGHT, MPSI_YOFFSET_BOTTOM);
				
}