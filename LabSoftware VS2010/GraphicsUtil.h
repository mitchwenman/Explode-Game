#ifndef GRAPHICSUTIL_
#define GRAPHICSUTIL_

#include "RGBColor.h"

#define ROUND(x) ((int)(x + 0.5))

typedef struct  {int x, y;} POINT2D;

typedef struct { int x; int y; RGBColour* c; } VERTEX;

typedef struct { int x; int y; int z; RGBColour* c; } VERTEX_3D;

#endif