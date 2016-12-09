///////////////////////////////////////////////////////////////////////////////////
// Filename: StatusDisplay.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Singleton manager for all status items. Draws each of them to the display.
///////////////////////////////////////////////////////////////////////////////////

//=======INCLUDES=========//
#include "StatusDisplay.h"

//==========GLOBALS========//
static StatusDisplay* _instance;

//=========FUNCTIONS========//

StatusDisplay* StatusDisplay::getSingleton()
{
	if (!_instance)
		_instance = new StatusDisplay();
	return _instance;
}

void StatusDisplay::draw()
{
	for (unsigned int i = 0; i < statusItems.size(); i++)
	{
		statusItems[i]->draw();
	}
}

void StatusDisplay::addStatusItem(IStatusItem *item)
{
	statusItems.push_back(item);
}