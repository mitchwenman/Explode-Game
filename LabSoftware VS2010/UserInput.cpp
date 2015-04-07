#include "UserInput.h"

#include "World.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DRotator.h"
#include "Polygon3DScaler.h"
#include "Polygon3DTranslator.h"
#include "Polygon3D.h"

static UserInput* _instance;

void UserInput::handleKeyInput(char key)
{
	if (selectedPolygon3D == -1 && key != '\t')
		return;
	World* world = World::getSingleton();
	switch (key)
	{
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