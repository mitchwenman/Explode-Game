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

	glRasterPos2i(300, 300);
	glutBitmapCharacter (GLUT_BITMAP_9_BY_15, 'H');

	
	

}