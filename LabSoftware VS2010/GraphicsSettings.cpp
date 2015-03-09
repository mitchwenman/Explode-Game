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

GraphicsSettings::GraphicsSettings() { }

void GraphicsSettings::setFrameDimensions(int width, int height)
{
	frameWidth = width;
	frameHeight = height;
}

void GraphicsSettings::setNumberOfChannels(int n)
{
	numberOfChannels = n;
}

void GraphicsSettings::setFrameBuffer(BYTE* buffer)
{
	frameBuffer = buffer;
}