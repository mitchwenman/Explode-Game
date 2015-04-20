#include "IStatusItem.h"
#include <string>

#define GAMEOVER_MESSAGE "GAME OVER: PRESS 'BACKSPACE' TO RESTART"

class GameOverStatusItem : public IStatusItem
{
private:


public:
	/******************
	Description: Interface method to draw the Game over status item to the screen. Only draws if game is over.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: void
	*******************///
	void draw();
};