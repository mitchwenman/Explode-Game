#pragma once

class IStatusItem
{
public:

	virtual ~IStatusItem() {}

	/******************
	Description: Interface method to draw status item details to screen. To be implemented by child.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: void
	*******************///
	virtual void draw() = 0;

};