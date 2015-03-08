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

typedef struct
{
	BYTE red, green, blue;
} RGBColour;

typedef struct
{
	int XTopVert, YTopVert, XLeftVert, YLeftVert, XRightVert, YRightVert;
	int hRight, hLeft;
	RGBColour* colourTop, *colourLeft, *colourRight;

} ScanLTriangle;



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
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBColour* colour1, RGBColour* colour2, RGBColour* colour3);
void calculateSLTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBColour* colour1, RGBColour* colour2, RGBColour* colour3, ScanLTriangle* slTri);


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
	/*for (int i = 0; i < 2; i++)
	{
		drawLine(rand() % FRAME_WIDE, rand() % FRAME_WIDE, rand() % FRAME_HIGH, rand() % FRAME_HIGH,
					rand() % 255, rand() % 255, rand() % 255, rand() % 255, rand() % 255, rand() % 255);
	}
	*/
	//Triangle test
	//drawLine(FRAME_WIDE/2, 0, FRAME_HIGH - 1, 0, 255, 255, 255);
	//drawLine(FRAME_WIDE/2, FRAME_WIDE - 1, FRAME_HIGH - 1, 200, 255, 255, 255);
	//drawLine(0, FRAME_WIDE - 1, 0, 200, 255, 255, 255);

	//for (int i = 0; i < 3; i++)
	//{
	RGBColour* colour1 = (RGBColour*)malloc(sizeof(RGBColour));
	RGBColour* colour2 = (RGBColour*)malloc(sizeof(RGBColour));
	RGBColour* colour3 = (RGBColour*)malloc(sizeof(RGBColour));
	colour1->red = 255; colour1->green = 0; colour1->blue = 0;
	colour2->red = 0; colour2->green = 255; colour2->blue = 0;
	colour3->red = 0; colour3->green = 0; colour3->blue = 255;
	drawTriangle(rand() % FRAME_WIDE, rand() % FRAME_HIGH, 
					rand() % FRAME_WIDE,rand() % FRAME_HIGH, 
					rand() % FRAME_WIDE, rand() % FRAME_HIGH, 
					colour1, colour2, colour3);
	Sleep(1000);
	free(colour1);
	free(colour2);
	free(colour3);
	//}
	
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

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,  RGBColour* colour1, RGBColour* colour2, RGBColour* colour3)
{
	ScanLTriangle* slTri = (ScanLTriangle*)malloc(sizeof(ScanLTriangle));
	calculateSLTriangle(x1, y1, x2, y2, x3, y3, colour1, colour2, colour3, slTri);
	
	//Assign left/right edges 
	double mL, mR;
	mL = (slTri->XLeftVert - slTri->XTopVert)/
		((double)slTri->YTopVert - slTri->YLeftVert);
	mR = (slTri->XRightVert - slTri->XTopVert)/
		((double)slTri->YTopVert - slTri->YRightVert);

	//Calculate colour deltas - left first
	double redML, blueML, greenML;
	double leftDenom = slTri->YTopVert - slTri->YLeftVert;
	redML = ((double)slTri->colourLeft->red - slTri->colourTop->red)/leftDenom;
	blueML = ((double)slTri->colourLeft->blue - slTri->colourTop->blue)/leftDenom;
	greenML = ((double)slTri->colourLeft->green - slTri->colourTop->green)/leftDenom;

	//Then right
	double redMR, greenMR, blueMR;
	double rightDenom = slTri->YTopVert - slTri->YRightVert; 
	redMR = ((double)slTri->colourRight->red - slTri->colourTop->red)/rightDenom;
	blueMR = ((double)slTri->colourRight->blue - slTri->colourTop->blue)/rightDenom;
	greenMR = ((double)slTri->colourRight->green - slTri->colourTop->green)/rightDenom;
	
	//Assign starting point and check for flat top
	double xL, xR;
	double clRed, clBlue, clGreen, crRed, crGreen, crBlue;
	if (slTri->YTopVert == slTri->YLeftVert)
	{
		xL = slTri->XLeftVert;
		clRed = slTri->colourLeft->red;
		clGreen = slTri->colourLeft->green;
		clBlue = slTri->colourLeft->blue;
		xR = slTri->XTopVert;
		crRed = slTri->colourTop->red;
		crGreen = slTri->colourTop->green;
		crBlue = slTri->colourTop->blue;
	} else if (slTri->YTopVert == slTri->YRightVert)
	{
		xL = slTri->XTopVert;
		clRed = slTri->colourTop->red;
		clGreen = slTri->colourTop->green;
		clBlue = slTri->colourTop->blue;
		
		xR = slTri->XRightVert;		
		crRed = slTri->colourRight->red;
		crGreen = slTri->colourRight->green;
		crBlue = slTri->colourRight->blue;
	} else 
	{
		xL = xR = slTri->XTopVert; 
		clRed = crRed = slTri->colourTop->red;
		clGreen = crGreen = slTri->colourTop->green;
		clBlue = crBlue = slTri->colourTop->blue;
	}
	
	//Find longest edge for end point
	int high = (slTri->hLeft > slTri->hRight) ? slTri->hLeft : slTri->hRight;
	for (int y = 0; y < high; y++)
	{
		//If we've reached a new edge - modify gradient so we can draw it
 		if (y == slTri->hLeft && slTri->hRight - slTri->hLeft == 0) break; //Only happens when flat bottom triangle
											//In which case - we're done anyway
		if (y == slTri->hLeft) //XXX: Divide by 0 possible if hR = hL
		{
			leftDenom = (double)(slTri->hRight - slTri->hLeft);
			mL = (slTri->XRightVert - xL)/leftDenom;
			redML = ((double)slTri->colourRight->red - slTri->colourLeft->red)/leftDenom;
			blueML = ((double)slTri->colourRight->blue - slTri->colourLeft->blue)/leftDenom;
			greenML = ((double)slTri->colourRight->green - slTri->colourLeft->green)/leftDenom;
		}
		if (y == slTri->hRight) 
		{
			rightDenom = (double)(slTri->hLeft - slTri->hRight);
			mR = (slTri->XLeftVert - xR)/rightDenom;
			redMR = ((double)slTri->colourLeft->red - slTri->colourRight->red)/rightDenom;
			blueMR = ((double)slTri->colourLeft->blue - slTri->colourRight->blue)/rightDenom;
			greenMR = ((double)slTri->colourLeft->green - slTri->colourRight->green)/rightDenom;
		}
		//y is the y-Offset from the starting point Y1
		drawLine(ceil(xL), ceil(xR - 1), slTri->YTopVert - y, slTri->YTopVert - y,
					clRed, clGreen,clBlue,
					crRed,crGreen, crBlue);
		xL += mL; xR += mR;
		clRed += redML; clBlue += blueML; clGreen += greenML;
		crRed += redMR; crBlue += blueMR; crGreen += greenMR;
	}
	free(slTri);

}

void calculateSLTriangle(int x1, int y1, int x2, int y2, int x3, int y3, 
							RGBColour* colour1, RGBColour* colour2, RGBColour* colour3, ScanLTriangle* slTri)
{
	int X0, X1, X2, Y0, Y1, Y2; //For holding vertices after (highest) is found
	RGBColour *c0, *c2;
	int max = max(max(y1, y2), y3);
	//Reassign to vars for rest of alg to work
	//Take X1, Y1 as top of triangle
	if (max == y1)
	{
		X1 = x1; Y1 = y1; slTri->colourTop = colour1;
		X0 = x2; Y0 = y2; c0 = colour2;
		X2 = x3; Y2 = y3; c2 = colour3;
	} else if (max == y2)
	{
		X1 = x2; Y1 = y2; slTri->colourTop = colour2;
		X0 = x1; Y0 = y1; c0 = colour1;
		X2 = x3; Y2 = y3; c2 = colour3;

	} else if (max == y3)
	{
		X1 = x3; Y1 = y3; slTri->colourTop = colour3;
		X0 = x1; Y0 = y1; c0 = colour1;
		X2 = x2; Y2 = y2; c2 = colour2;
	}
	double edgeA, edgeB;
	edgeA = atan2((double)Y2 - Y1, X2 - X1); 
	edgeB = atan2((double)Y0 - Y1, X0 - X1);	
	//Assign left/right edges 	
	if (edgeA > edgeB)
	{
		slTri->hLeft = Y1 - Y0;
		slTri->hRight = Y1 - Y2;
		slTri->XLeftVert = X0;
		slTri->YLeftVert = Y0;
		slTri->XRightVert = X2;
		slTri->YRightVert = Y2;
		slTri->colourLeft = c0;
		slTri->colourRight = c2;
	} else
	{
		slTri->hRight = Y1 - Y0;
		slTri->hLeft = Y1 - Y2;
		slTri->XLeftVert = X2;
		slTri->YLeftVert = Y2;
		slTri->XRightVert = X0;
		slTri->YRightVert = Y0;
		slTri->colourLeft = c2;
		slTri->colourRight = c0;
	}
	slTri->XTopVert = X1;
	slTri->YTopVert = Y1;	
	
}

