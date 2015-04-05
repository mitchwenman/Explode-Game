#include "ZBuffer.h"

static ZBuffer* _instance;

ZBuffer* ZBuffer::getSingleton()
{
	if (!_instance)
		_instance = new ZBuffer();
	return _instance;
}

bool ZBuffer::shouldDrawPixel(int x, int y, int z)
{
	std::pair<int, int> verts = std::make_pair(x, y);
	if (this->zBuffer.count(verts) == 1)
	{
		int existingZ = zBuffer[verts];
		if (z < existingZ)
			zBuffer[verts] = z;
		else
			return false;
	} else
		zBuffer[verts] = z;
	return true;
}

void ZBuffer::flush()
{
	zBuffer.clear();
}



