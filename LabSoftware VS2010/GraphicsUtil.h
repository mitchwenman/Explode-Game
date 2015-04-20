#pragma once

#include "RGBColor.h"
#include <string>

/* A utility file for random but useful functions/types */

typedef struct { int x; int y; RGBColour c; } VERTEX;

typedef struct { double x; double y; double z; RGBColour c; } VERTEX_3D;

typedef struct { double x; double y; double z; } VERTEX_3D_f;

namespace GraphicsUtil
{
	/******************
	Description: Draws a bitmapped string to the x and y coordinate
	Parameters: void *font: The font (usually GLUT_*)
				string str: the string to be written
				int x, y  : The x and y coordinates of where the string will be written.
	Preconditions: NIL
	Postconditions: Frame buffer is modified.
	Returns: void
	*******************///
	void drawString(void *font, std::string str, int x, int y);
};






