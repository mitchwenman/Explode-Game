#include "IStatusItem.h"

class MissedPolygonStatusItem : public IStatusItem
{
private:
	static const int MPSI_XOFFSET_RIGHT = 500;
	static const int MPSI_YOFFSET_BOTTOM = 25;

public:
	/******************
	Description: Draws a the number of missed polygons to the screen.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: void
	*******************///
	void draw();

};