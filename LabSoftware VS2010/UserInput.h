#pragma once

#include "Polygon3D.h"
#include "World.h"

class UserInput
{
	

public:
	//Mega-method to handle key inputs
	void handleKeyInput(char key);

	//Returns the user input singleton
	static UserInput* getSingleton();

private:
	//Private constructor for singleton
	UserInput();
	virtual ~UserInput() {}

	int selectedPolygon3D;
	int selectedPolygon2D;
	
	//A copy of the world instance
	World* world;
};
