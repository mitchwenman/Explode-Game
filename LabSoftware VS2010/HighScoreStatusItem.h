#include "IStatusItem.h"

class HighScoreStatusItem : public IStatusItem
{
private:
	static const int X_OFFSET_LEFT = 100;
	static const int Y_OFFSET_BOTTOM = 25;

public:

	/******************
	Description: Interface method to draw the high score to the screen.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: void
	*******************/
	void draw();

};