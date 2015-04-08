#pragma once

#include "Polygon3D.h"
#include "World.h"

class UserInput
{
	

public:
	int selectedPolygon3D;
	int selectedPolygon2D;

	//Mega-method to handle key inputs
	void handleKeyInput(char key);

	//Mouse input method
	void handleMouseInput(int button, int state, int x, int y) {};
	
	//Returns the user input singleton
	static UserInput* getSingleton();

private:
	//Private constructor for singleton
	UserInput();
	virtual ~UserInput() {}


	
	//A copy of the world instance
	World* world;
};
