#include "IStatusItem.h"
#include <string>

#define GAMEOVER_MESSAGE "GAME OVER: PRESS 'BACKSPACE' TO RESTART"

class GameOverStatusItem : public IStatusItem
{
private:


public:
	//Interface method to draw status item
	void draw();
};