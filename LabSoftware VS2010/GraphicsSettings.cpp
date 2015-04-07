#include "GraphicsSettings.h"

static GraphicsSettings* _instance;

GraphicsSettings* GraphicsSettings::getGraphicsSettings()
{
	if (!_instance)
	{
		_instance = new GraphicsSettings();
	}
	return _instance;
}



