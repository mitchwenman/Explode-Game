#include "ScoreStatusItem.h"
#include "Game.h"

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
	
	glRasterPos2i(200, 200);
	glColor3b(255, 255, 255);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
}