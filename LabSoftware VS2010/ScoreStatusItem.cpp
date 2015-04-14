#include "ScoreStatusItem.h"
#include "Game.h"
#include "GraphicsUtil.h"
#include "GraphicsSettings.h"
#include "libs\glut.h"
#include <string>
#include <sstream>
void ScoreStatusItem::draw()
{
	Game *game = Game::getSingleton();
	int currScore = game->getScore();
	GraphicsSettings *gset = gset->getGraphicsSettings();
	std::stringstream stream;
	stream << "Score: " << currScore;

	GraphicsUtil::drawString(GLUT_BITMAP_TIMES_ROMAN_24, stream.str() , 
		gset->getFrameWidth() - SCORESI_XOFFSET_RIGHT, 
		SCORESI_YOFFSET_BOTTOM);
	
	

}