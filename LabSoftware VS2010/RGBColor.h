#ifndef RGBCOLOUR_
#define RGBCOLOUR_

#define RED_OFFSET 0
#define GREEN_OFFSET 1
#define BLUE_OFFSET 2

typedef unsigned char BYTE;

typedef struct RGBColour
{
	BYTE red, green, blue;
} RGBColour;

#endif