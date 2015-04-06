#pragma once

#include "GraphicsSettings.h"
#include <vector>

class ZBuffer
{

private:

	static const int DEFAULT_DEPTH = 10000;

	ZBuffer(void);

	GraphicsSettings* graphicsSettings;

	std::vector<std::vector<int>> zBuffer;

public:
	
	static ZBuffer* getSingleton();

	bool shouldDrawPixel(int x, int y, int z);

	void flush();

	~ZBuffer(void) { };
};

