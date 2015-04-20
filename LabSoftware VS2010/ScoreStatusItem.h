#include "IStatusItem.h"

class ScoreStatusItem : public IStatusItem
{
private:
	static const int SCORESI_XOFFSET_RIGHT = 200;
	static const int SCORESI_YOFFSET_BOTTOM =  25;

public:

	/******************
	Description:Interface method for drawing score to the screen.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  NIL
	*******************/
	void draw();

};