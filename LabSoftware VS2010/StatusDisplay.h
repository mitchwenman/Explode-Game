#pragma once

#include "IStatusItem.h"
#include <vector>

class StatusDisplay
{
private:

	//The list of status items that will be displayed
	std::vector<IStatusItem *> statusItems;

	/******************
	Description: Private constructor for singleton pattern.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  
	*******************/
	StatusDisplay() {};

public:
	
	/******************
	Description: Draws all status items in statusItems to the display by invoking their draw function.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void draw();

	/******************
	Description: Inserts a status item into statusItems.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: statusItems is modified.
	Returns:  void
	*******************/
	void addStatusItem(IStatusItem *item);

	/******************
	Description: Creates if needed and returns singleton StatusDisplay object.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  The status display singleton object.
	*******************/
	static StatusDisplay* getSingleton();
};