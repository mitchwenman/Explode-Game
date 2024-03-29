///////////////////////////////////////////////////////////////////////////////////
// Filename: UserInput.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Class for managing user key/mouse input.
///////////////////////////////////////////////////////////////////////////////////


//=======INCLUDES=========//
#include "UserInput.h"

#include "World.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DRotator.h"
#include "Polygon3DScaler.h"
#include "Polygon3DTranslator.h"
#include "Polygon3D.h"
#include "ExplodedPolygonManager.h"
#include "SoundEffect.h"
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

//==========GLOBALS========//
static UserInput* _instance;

//=========FUNCTIONS========//
void UserInput::handleKeyInput(char key)
{
	if (selectedPolygon3D == -1 && key != '\t')
		return;
	World* world = World::getSingleton();
	switch (key)
	{
	case 8:
		{
			Game *game = Game::getSingleton();
			GameStatus currentStatus = game->getCurrentStatus();
			if (currentStatus == GSTATUS_RUNNING)
				game->setStatus(GSTATUS_OVER);
			else
				game->setStatus(GSTATUS_RUNNING);
			break;
		}
	case '\t':
		{
			selectedPolygon3D = (selectedPolygon3D + 2) % (world->polygon3ds.size() + 1) - 1;
			break;
		}
	case 'w': 
		{			
			world->translate3DPolyAtIndex(selectedPolygon3D, 0, 0, 10);
			break;
		}
	case 's':
		{
			world->translate3DPolyAtIndex(selectedPolygon3D, 0, 0, -10);
			break;
		}
	case 'a':
		{
			world->translate3DPolyAtIndex(selectedPolygon3D, -10, 0, 0);
			break;
		}
	case 'd':
		{
			world->translate3DPolyAtIndex(selectedPolygon3D, 10, 0, 0);
			break;
		}
	case 'r':
		{
			world->translate3DPolyAtIndex(selectedPolygon3D, 0, 10, 0);
			break;
		}
	case 'f':
		{
			world->translate3DPolyAtIndex(selectedPolygon3D, 0, -10, 0);
			break;
		}
	case '7':
		{
			world->scale3DPolyAtIndex(selectedPolygon3D, 1.1, 1, 1);
			break;
		}
	case '4':
		{
			world->scale3DPolyAtIndex(selectedPolygon3D, 0.9, 1, 1);
			break;
		}
	case '8':
		{
			world->scale3DPolyAtIndex(selectedPolygon3D, 1, 1.1, 1);
			break;
		}
	case '5':
		{
			world->scale3DPolyAtIndex(selectedPolygon3D, 1, 0.9, 1);
			break;
		}
	case '9':
		{
			world->scale3DPolyAtIndex(selectedPolygon3D, 1, 1, 1.1);
			break;
		}
	case '6':
		{
			world->scale3DPolyAtIndex(selectedPolygon3D, 1, 1, 0.9);
			break;
		}
	case 'z':
		{
			world->rotate3DPolyAtIndex(selectedPolygon3D, 0, 0, 5);
			break;
		}
	case 'x':
		{
			world->rotate3DPolyAtIndex(selectedPolygon3D, 5, 0, 0);
			break;
		}
	case 'y':
		{
			world->rotate3DPolyAtIndex(selectedPolygon3D, 0, 5, 0);
			break;
		}
	
	}
		
	
	
	
}

void UserInput::handleMouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
		int index = ExplodedPolygonManager::getSingleton()->explodePolygonAtCoords(x, y);
		if (index != -1)
		{
			
			Game* game = Game::getSingleton();
			int oldHighscore = game->highScore;
			int oldScore = game->getScore();
			int newScore = game->incrementScore();
			int newHighScore = game->highScore;
			if (newHighScore == newScore && oldScore != oldHighscore)
				SoundEffect::playRewardSoundEffect();
			else
				SoundEffect::playPolygonHitSoundEffect();
		} else
		{
			SoundEffect::playClickSoundEffect();
		}
	}
}

UserInput* UserInput::getSingleton()
{
	if (!_instance)
		_instance = new UserInput();
	return _instance;
}

UserInput::UserInput()
{
	selectedPolygon2D = selectedPolygon3D = 0;
	world = World::getSingleton();
}