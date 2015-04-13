#include "StatusDisplay.h"

static StatusDisplay* _instance;

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