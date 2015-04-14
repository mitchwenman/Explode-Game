#include "IStatusItem.h"

class ScoreStatusItem : public IStatusItem
{
private:
	static const int SCORESI_XOFFSET_RIGHT = 200;
	static const int SCORESI_YOFFSET_BOTTOM =  25;

public:
	void draw();

};