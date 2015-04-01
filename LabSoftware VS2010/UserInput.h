#pragma once

#include "Polygon3D.h"
#include "World.h"

class UserInput
{
	

public:
	void handleKeyInput(char key);

	static UserInput* getSingleton();

private:
	UserInput();
	virtual ~UserInput() {}

	int selectedPolygon3D;
	int selectedPolygon2D;
	World* world;
};
