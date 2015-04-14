#include "GraphicsUtil.h"

#ifdef _WIN32
	#include "libs/glut.h"
	#include <windows.h>
	#pragma comment(lib, "winmm.lib")			//- not required but have it in anyway
	#pragma comment(lib, "libs/glut32.lib")
#elif __APPLE__
	#include <GLUT/glut.h>
#elif __unix__		// all unices including  __linux__
	#include <GL/glut.h>
#endif

void GraphicsUtil::drawString(void *font, std::string str, int x, int y)
{
	glRasterPos2i(x, y);
	for (unsigned int i = 0; i < str.length(); i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}