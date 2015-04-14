#include "GameOverStatusItem.h"
#include "GraphicsUtil.h"
#include "GraphicsSettings.h"
#include "Game.h"
#include "libs\glut.h"

#include <sstream>

void GameOverStatusItem::draw()
{
	if (Game::getSingleton()->getCurrentStatus() == GSTATUS_OVER)
	{
		GraphicsSettings *gset = GraphicsSettings::getGraphicsSettings();
		int x = gset->getFrameWidth() / 2 - 250;
		int y = gset->getFrameHeight() / 2 - 5;
		GraphicsUtil::drawString(GLUT_BITMAP_TIMES_ROMAN_24, GAMEOVER_MESSAGE, x, y);
	}
}