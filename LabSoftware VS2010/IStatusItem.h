#pragma once

class IStatusItem
{
public:

	virtual ~IStatusItem() {}

	virtual void draw() = 0;

};