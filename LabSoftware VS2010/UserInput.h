#pragma once

#include "Polygon3D.h"
#include "World.h"

class UserInput
{
	

public:
	int selectedPolygon3D;
	int selectedPolygon2D;

	/******************
	Description:Performs the correct opertion given the key pressed
	Parameters: char key: The key that was pressed.
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void handleKeyInput(char key);

	/******************
	Description:Event handler for mouse input
	Parameters: int button: The left, middle, right mouse button
				int state: Is the button up or down.
				int x, y: The coordinates of where the mouse was clicked.
	Preconditions: 0 <= x <= 360
	Postconditions: NIL
	Returns:  void
	*******************/
	void handleMouseInput(int button, int state, int x, int y);
	
	/******************
	Description:Creates if needed and returns user input singleton object
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  The user input singleton
	*******************/
	static UserInput* getSingleton();

private:
	/******************
	Description:Private constructor for singleton pattern
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  
	*******************/
	UserInput();
	virtual ~UserInput() {}


	
	//A copy of the world instance
	World* world;
};
