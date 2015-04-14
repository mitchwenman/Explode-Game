#pragma once

#include "RGBColor.h"
#include <string>

/* A utility file for random but useful functions/types */

namespace GraphicsUtil
{
	//Draws a string to the frame
	void drawString(void *font, std::string str, int x, int y);
}


#define ROUND(x) ((int)(x + 0.5))

typedef struct  {int x, y;} POINT2D;

typedef struct { int x; int y; RGBColour c; } VERTEX;

typedef struct { double x; double y; double z; RGBColour c; } VERTEX_3D;

typedef struct { double x; double y; double z; } VERTEX_3D_f;



