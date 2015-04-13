#pragma once

#include "IStatusItem.h"
#include <vector>

class StatusDisplay
{
private:

	//The list of status items that will be displayed
	std::vector<IStatusItem *> statusItems;

	StatusDisplay() {};

public:
	
	//Draws the status display by invoking each status item's
	//draw method
	void draw();

	//Adds a status item to the display
	void addStatusItem(IStatusItem *item);

	//Returns the singleton object
	static StatusDisplay* getSingleton();
};