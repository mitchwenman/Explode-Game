#include "TrigLookup.h"

#include <math.h>

static TrigLookup* _instance;


TrigLookup* TrigLookup::getSingleton()
{
	if (!_instance)
		_instance = new TrigLookup();
	return _instance;
}

double TrigLookup::cos(int x)
{
	return this->cosLookup[x];
}

double TrigLookup::sin(int x)
{
	return this->sinLookup[x];
}

TrigLookup::TrigLookup()
{
	for (unsigned int i = 0; i < MAX_VALUES; i++)
	{
		this->cosLookup[i] = cos(i);
		this->sinLookup[i] = sin(i);
	}
}