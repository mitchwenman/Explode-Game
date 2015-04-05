#pragma once

#include <map>

class ZBuffer
{

private:
	ZBuffer(void) {};

	std::map<std::pair<int, int>, int> zBuffer;

public:
	
	static ZBuffer* getSingleton();

	bool shouldDrawPixel(int x, int y, int z);

	~ZBuffer(void) { };
};

