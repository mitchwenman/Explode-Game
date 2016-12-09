///////////////////////////////////////////////////////////////////////////////////
// Filename: GameOverStatusItem.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Implements IStatusItem. Draws the game over message to the screen.
///////////////////////////////////////////////////////////////////////////////////

//=======INCLUDES=========//
#include "GameOverStatusItem.h"
#include "GraphicsUtil.h"
#include "GraphicsSettings.h"
#include "Game.h"
#include "libs\glut.h"

#include <sstream>


//=========FUNCTIONS========//

void GameOverStatusItem::draw()
{
	if (Game::getSingleton()->getCurrentStatus() == GSTATUS_OVER)
	{
		GraphicsSettings *gset = GraphicsSettings::getGraphicsSettings();
		int x = gset->getFrameWidth() / 2 - 250;
		int y = gset->getFrameHeight() / 2 - 5;
		glColor3f(1.0, 1.0, 0.0);
		GraphicsUtil::drawString(GLUT_BITMAP_TIMES_ROMAN_24, GAMEOVER_MESSAGE, x, y);
		
	}
}