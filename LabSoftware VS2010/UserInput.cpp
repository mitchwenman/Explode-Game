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
	Polygon3D *p;
	
	if (world->polygon3ds.size() > selectedPolygon3D)
	{
		p = world->polygon3ds[selectedPolygon3D];
	} else if (selectedPolygon3D == -1 && key != '\t')
		return;

	switch (key)
	{
	case '\t':
		{
			selectedPolygon3D = (selectedPolygon3D + 2) % (world->polygon3ds.size() + 1) - 1;
			break;
		}
	case 'w': 
		{			
			Polygon3DTranslator::translate(p, 0, 0, 10);
			break;
		}
	case 's':
		{
			Polygon3DTranslator::translate(p, 0, 0, -10);
			break;
		}
	case 'a':
		{
			Polygon3DTranslator::translate(p, -10, 0, 0);
			break;
		}
	case 'd':
		{
			Polygon3DTranslator::translate(p, 10, 0, 0);
			break;
		}
	case 'r':
		{
			Polygon3DTranslator::translate(p, 0, 10, 0);
			break;
		}
	case 'f':
		{
			Polygon3DTranslator::translate(p, 0, -10, 0);
			break;
		}
	case '7':
		{
			Polygon3DScaler::scale(p, 1.1, 1, 1);
			break;
		}
	case '4':
		{
			Polygon3DScaler::scale(p, 0.9, 1, 1);
			break;
		}
	case '8':
		{
			Polygon3DScaler::scale(p, 1, 1.1, 1);
			break;
		}
	case '5':
		{
			Polygon3DScaler::scale(p, 1, 0.9, 1);
			break;
		}
	case '9':
		{
			Polygon3DScaler::scale(p, 1, 1, 1.1);
			break;
		}
	case '6':
		{
			Polygon3DScaler::scale(p, 1, 1, 0.9);
			break;
		}
	case 'z':
		{
			Polygon3DRotator::Rotate(p, 0, 0, 1);
			break;
		}
	case 'x':
		{
			Polygon3DRotator::Rotate(p, 1, 0, 0);
			break;
		}
	case 'y':
		{
			Polygon3DRotator::Rotate(p, 0, 1, 0);
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