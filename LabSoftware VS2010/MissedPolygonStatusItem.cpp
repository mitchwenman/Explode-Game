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
	GraphicsUtil::drawString(GLUT_BITMAP_TIMES_ROMAN_24, stream.str(),
		gset->getFrameWidth() - MPSI_XOFFSET_RIGHT, MPSI_YOFFSET_BOTTOM);
				
}