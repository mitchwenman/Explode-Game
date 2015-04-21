///////////////////////////////////////////////////////////////////////////////////
// Filename: ZBuffer.cpp
// Author: Mitch Wenman
// Date Modified: 21/04/2015
// Description: Implementation of a ZBuffer.
///////////////////////////////////////////////////////////////////////////////////

#include "ZBuffer.h"
#include <iostream>
static ZBuffer* _instance;

ZBuffer::ZBuffer(void)
{
	graphicsSettings = GraphicsSettings::getGraphicsSettings();
	int frameWidth = graphicsSettings->getFrameWidth();
	int frameHeight = graphicsSettings->getFrameHeight();
	zBuffer.resize(frameWidth);
	for (int i = 0; i < frameWidth; i++)
		zBuffer[i].resize(frameHeight);
	flush();
}

ZBuffer* ZBuffer::getSingleton()
{
	if (!_instance)
		_instance = new ZBuffer();
	return _instance;
}

bool ZBuffer::shouldDrawPixel(int x, int y, int z)
{	
	if (z < MIN_Z_RENDER) return false;
	if (zBuffer[x][y] > z)
	{
		zBuffer[x][y] = z;
		return true;
	} else
		return false;
}

void ZBuffer::flush()
{
	int frameWidth = graphicsSettings->getFrameWidth();
	int frameHeight = graphicsSettings->getFrameHeight();
	for (int i = 0; i < frameWidth; i++)
	{
		for (int j = 0; j < frameHeight; j++)
		{
			zBuffer[i][j] = DEFAULT_DEPTH;
		}
	}
}



