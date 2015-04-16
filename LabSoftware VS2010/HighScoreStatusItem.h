#include "IStatusItem.h"

class HighScoreStatusItem : public IStatusItem
{
private:
	static const int X_OFFSET_LEFT = 100;
	static const int Y_OFFSET_BOTTOM = 25;

public:
	void draw();

};