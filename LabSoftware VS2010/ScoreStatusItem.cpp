#include "ScoreStatusItem.h"
#include "Game.h"
#include "GraphicsSettings.h"

#ifdef _WIN32
	#include "libs/glut.h"
	#include <windows.h>
	#pragma comment(lib, "winmm.lib")			//- not required but have it in anyway
	#pragma comment(lib, "libs/glut32.lib")
#elif __APPLE__
	#include <GLUT/glut.h>
#elif __unix__		// all unices including  __linux__
	#include <GL/glut.h>
#endif

void ScoreStatusItem::draw()
{
	Game *game = Game::getSingleton();
	int currScore = game->getScore();
	GraphicsSettings *gset = GraphicsSettings::getGraphicsSettings();

	glLoadIdentity();
	glOrtho(0.0f, gset->getFrameWidth(), 0.0f, 0.0f, gset->getFrameHeight(), 0.0f);
	glRasterPos2i(300, 300);
	 glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);
	
	glutBitmapCharacter (GLUT_BITMAP_9_BY_15, 'H');
	 glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);
	
	

}