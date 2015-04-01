#include "UserInput.h"

#include "World.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DRotator.h"
#include "Polygon3DTranslator.h"
#include "Polygon3D.h"

static UserInput* _instance;

void UserInput::handleKeyInput(char key)
{
	
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