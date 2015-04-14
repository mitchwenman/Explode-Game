#include "IStatusItem.h"

class MissedPolygonStatusItem : public IStatusItem
{
private:
	static const int MPSI_XOFFSET_RIGHT = 500;
	static const int MPSI_YOFFSET_BOTTOM = 25;

public:
	void draw();

};