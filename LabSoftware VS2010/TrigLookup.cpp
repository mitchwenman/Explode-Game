#include "TrigLookup.h"
#ifdef _WIN32
	#include <windows.h>
#endif
#include <math.h>

static TrigLookup* _instance;


TrigLookup* TrigLookup::getSingleton()
{
	if (!_instance)
		_instance = new TrigLookup();
	return _instance;
}

double TrigLookup::cosLookup(int x)
{
	return this->cosL[x];
}

double TrigLookup::sinLookup(int x)
{
	return this->sinL[x];
}

TrigLookup::TrigLookup()
{
	for (unsigned int i = 0; i < MAX_VALUES; i++)
	{
		this->cosL[i] = cos((double)((2 * PI * i) / 360));
		this->sinL[i] = sin((double)((2 * PI * i) / 360));
	}
}