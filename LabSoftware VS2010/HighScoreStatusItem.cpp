///////////////////////////////////////////////////////////////////////////////////
// Filename: HighScoreStatusItem.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Implements IStatusItem. Draws high score to the display.
///////////////////////////////////////////////////////////////////////////////////

#include "HighScoreStatusItem.h"
#include "Game.h"
#include "GraphicsUtil.h"
#include "libs\glut.h"

#include <string>
#include <sstream>

void HighScoreStatusItem::draw()
{
	Game* game = Game::getSingleton();
	int highScore = game->highScore;
	int score = game->getScore();
	
	std::stringstream stream;
	stream << "High Score: " << highScore;
	if (highScore == score)
		glColor3f(0, 1.0, 0.5);
	else
		glColor3f(1, 1, 1);
	GraphicsUtil::drawString(GLUT_BITMAP_TIMES_ROMAN_24, stream.str(), 
							X_OFFSET_LEFT, Y_OFFSET_BOTTOM);
}