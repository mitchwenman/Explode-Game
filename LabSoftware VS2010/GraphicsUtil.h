#pragma once

#include "RGBColor.h"
#include <string>

/* A utility file for random but useful functions/types */

typedef struct { int x; int y; RGBColour c; } VERTEX;

typedef struct { double x; double y; double z; RGBColour c; } VERTEX_3D;

typedef struct { double x; double y; double z; } VERTEX_3D_f;

namespace GraphicsUtil
{
	//Draws a string to the frame
	void drawString(void *font, std::string str, int x, int y);
};






