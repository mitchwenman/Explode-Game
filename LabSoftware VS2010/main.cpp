#include <stdlib.h>			//- for exit()
#include <stdio.h>			//- for sprintf()
#include <string.h>			//- for memset()
#include <math.h>

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

//====== Macros and Defines =========

#define FRAME_WIDE	1000
#define FRAME_HIGH	600

#define ROUND(x) ((int)(x + 0.5))

//====== Structs & typedefs =========
typedef unsigned char BYTE;
struct POINT2D {int x, y;};
typedef struct 
{ 
	int x1, x2, y1, y2;
	double steps, xInc, yInc; 
} DDALine;

//====== Global Variables ==========
BYTE	pFrameL[FRAME_WIDE * FRAME_HIGH * 3];
BYTE	pFrameR[FRAME_WIDE * FRAME_HIGH * 3];
int		NUM_CHANNELS = 3;
int		shade = 0;
POINT2D	xypos = {0,0};
int		stereo = 0;
int		eyes = 10;

//===== Forward Declarations ========
void ClearScreen();
void DrawFrame();
void Interlace(BYTE* pL, BYTE* pR);
void PlaySoundEffect(char * filename);
void BuildFrame(BYTE *pFrame, int view);
void OnIdle(void);
void OnDisplay(void);
void reshape(int w, int h);
void OnMouse(int button, int state, int x, int y);
void OnKeypress(unsigned char key, int x, int y);
void setPixel(int x, int y, BYTE r, BYTE g, BYTE b);
void drawLine(int x1, int x2, int y1, int y2, BYTE r, BYTE g, BYTE b);
void drawLine(int x1, int x2, int y1, int y2, BYTE r1,BYTE g1,BYTE b1, BYTE r2,BYTE g2,BYTE b2);
void calculateDDALine(DDALine* ddaLine);

////////////////////////////////////////////////////////
// Program Entry Poinr
////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	//-- setup GLUT --
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	//GLUT_3_2_CORE_PROFILE |
	glutInitWindowSize(FRAME_WIDE, FRAME_HIGH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
/*
#ifdef WIN32
	//- eliminate flashing --
	typedef void (APIENTRY * PFNWGLEXTSWAPCONTROLPROC) (int i);
	PFNWGLEXTSWAPCONTROLPROC wglSwapControl = NULL;
	wglSwapControl = (PFNWGLEXTSWAPCONTROLPROC) wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapControl != NULL) wglSwapControl(1); 
#endif
*/

	//--- set openGL state --
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//-- register call back functions --
	glutIdleFunc(OnIdle);
	glutDisplayFunc(OnDisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(OnKeypress);
	glutMouseFunc(OnMouse);

	//-- run the program
	glutMainLoop();
	return 0;
}


////////////////////////////////////////////////////////
// Event Handers
////////////////////////////////////////////////////////
      
void OnIdle(void)
{
	DrawFrame();
	glutPostRedisplay();
}


void OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);
	glDrawPixels(FRAME_WIDE, FRAME_HIGH, GL_RGB,GL_UNSIGNED_BYTE, (GLubyte*)pFrameR);
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void OnMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		PlaySoundEffect("Laser.wav"); 
		if (++shade > 16) shade = 0;	
	}
}

void OnKeypress(unsigned char key, int x, int y)
{
	switch (key) 
	{ 
	case ' ': xypos.x = xypos.y = 0; break;
	case 's': stereo ^= 1, eyes = 10;break;
	case ']': eyes++;	break;
	case '[': eyes--;	break;
	case 27 : exit(0);
	}
	PlaySoundEffect("Whoosh.wav"); 
}


////////////////////////////////////////////////////////
// Utility Functions
////////////////////////////////////////////////////////


void ClearScreen()
{
	memset(pFrameL, 0, FRAME_WIDE * FRAME_HIGH * 3);
	memset(pFrameR, 0, FRAME_WIDE * FRAME_HIGH * 3);
}


void Interlace(BYTE* pL, BYTE* pR)
{
	int rowlen = 3 * FRAME_WIDE;
	for (int y = 0; y < FRAME_HIGH; y+=2)
	{
		for (int x = 0; x < rowlen; x++) *pR++ = *pL++;
		pL += rowlen;
		pR += rowlen;
	}
}


void DrawFrame()
{
	ClearScreen();
	
	if (!stereo) BuildFrame(pFrameR, 0);
	else {
		BuildFrame(pFrameL, -eyes);
		BuildFrame(pFrameR, +eyes);
		Interlace((BYTE*)pFrameL, (BYTE*)pFrameR);
	}
}

void	PlaySoundEffect(char * filename)		
{
#ifdef _WIN32
	PlaySound(filename, NULL, SND_ASYNC | SND_FILENAME ); 
#else
	char command[80];
	#ifdef __APPLE__
		sprintf(command, "afplay %s &", filename);
	#else
		sprintf(command, "play %s &", filename);
	#endif	
	system(command);
#endif
}

////////////////////////////////////////////////////////
// Drawing Function
////////////////////////////////////////////////////////

void BuildFrame(BYTE *pFrame, int view)
{
	
	BYTE*	screen = (BYTE*)pFrame;		// use copy of screen pointer for safety
	for (int i = 0; i < 2; i++)
	{
		drawLine(rand() % FRAME_WIDE, rand() % FRAME_WIDE, rand() % FRAME_HIGH, rand() % FRAME_HIGH,
					rand() % 255, rand() % 255, rand() % 255, rand() % 255, rand() % 255, rand() % 255);
	}
	
}


void setPixel(int x, int y, BYTE r, BYTE g, BYTE b)
{
	BYTE* screen = (BYTE*)pFrameR; 
	enum CHANNEL_OFFSET { RED, GREEN, BLUE}; //Channel offsets
	//Set red, green and blue
	screen[NUM_CHANNELS * (x + y * FRAME_WIDE) + RED] = r;
	screen[NUM_CHANNELS * (x + y * FRAME_WIDE) + GREEN] = g;
	screen[NUM_CHANNELS * (x + y * FRAME_WIDE) + BLUE] = b;
}

void drawLine(int x1, int x2, int y1, int y2, BYTE r, BYTE g, BYTE b)
{
	//Create DDALine type for calculation
	DDALine* dda = new DDALine;
	dda->x1 = x1; dda->x2 = x2; dda->y1 = y1; dda->y2 = y2;
	calculateDDALine(dda);
	//Create x,y double vars for better rounding
	double x = x1;
	double y = y1;
	//Draw the line
	for (int i = 0; i < dda->steps; i++)
	{
		setPixel(ROUND(x), ROUND(y), r, g, b);
		x += dda->xInc;
		y += dda->yInc;
	}
}

void calculateDDALine(DDALine* ddaLine)
{
	//Find axis of greatest change
	int dx = ddaLine->x2 - ddaLine->x1;
	int dy = ddaLine->y2 - ddaLine->y1;
	int steps;
	if (abs(dx) > abs(dy)) 
		steps = abs(dx);
	else
		steps = abs(dy);
	//Calculate increments for both axes
	double xInc, yInc;
	xInc = dx / (double) steps;
	yInc = dy / (double) steps;
	//Place in struct
	ddaLine->steps = steps;
	ddaLine->xInc = xInc;
	ddaLine->yInc = yInc;
}

void drawLine(int x1, int x2, int y1, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2)
{
	//Create DDALine type for calculation
	DDALine* dda = new DDALine;
	dda->x1 = x1; dda->x2 = x2; dda->y1 = y1; dda->y2 = y2;
	calculateDDALine(dda);
	//Create x,y double vars for better rounding
	double x = x1;
	double y = y1;
	//Calculate colour diffs
	double r, g, b, rdiff, gdiff, bdiff;
	r = (double)r1; g = (double)g1; b = (double)b1;
	rdiff = (r2 - r1)/dda->steps;
	gdiff = (g2 - g1)/dda->steps;
	bdiff = (b2 - b1)/dda->steps;
	//Draw the line
	for (int i = 0; i < dda->steps; i++)
	{
		setPixel(ROUND(x), ROUND(y), (int)r, (int)g, (int)b);
		x += dda->xInc;
		y += dda->yInc;
		r += rdiff; 
		g += gdiff;
		b += bdiff;
	}
}