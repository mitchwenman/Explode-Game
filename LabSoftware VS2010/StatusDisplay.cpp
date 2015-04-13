#include "StatusDisplay.h"

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