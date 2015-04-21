///////////////////////////////////////////////////////////////////////////////////
// Filename: GraphicsSettings.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Singleton class for mananging the frame height/width, fov etc.
///////////////////////////////////////////////////////////////////////////////////

#include "GraphicsSettings.h"
#include <Windows.h>

static GraphicsSettings* _instance;

GraphicsSettings* GraphicsSettings::getGraphicsSettings()
{
	if (!_instance)
	{
		_instance = new GraphicsSettings();
	}
	return _instance;
}


bool GraphicsSettings::shouldAnimate()
{
	DWORD now = GetTickCount();
	if (now - lastUpdate > ANIMATE_RATE)
	{
		lastUpdate = now;
		return true;
	}
	
	return false;
}

GraphicsSettings::GraphicsSettings()
{
	ANIMATE_RATE = 45;
	lastUpdate = GetTickCount();
}
