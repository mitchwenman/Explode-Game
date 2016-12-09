#pragma once

#include "GraphicsSettings.h"
#include <vector>

class ZBuffer
{

private:

	static const int DEFAULT_DEPTH = 10000;

	/******************
	Description:Private constructor for singleton pattern. Populates ZBuffer with maximum values.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  
	*******************/
	ZBuffer(void);

	GraphicsSettings* graphicsSettings;

	std::vector<std::vector<int>> zBuffer;

public:
	/******************
	Description:Creates if needed and returns Zbuffer singleton
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  The Zbuffer singleton
	*******************/	
	static ZBuffer* getSingleton();

	/******************
	Description:Tests if a pixel should be drawn by checking the Z Buffer
	Parameters: NIL
	Preconditions: int x, y, z: The x, y and z values of the pixel
	Postconditions: value of (x, y) in buffer is changed to z if function returns true
	Returns: True if the pixel is closer to the user than the current pixel, else false
	*******************/
	bool shouldDrawPixel(int x, int y, int z);

	/******************
	Description:Resets all values in the buffer to the original maximum
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void flush();

	~ZBuffer(void) { };
};

