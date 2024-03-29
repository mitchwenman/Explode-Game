#include <stdlib.h>			//- for exit()
#include <stdio.h>			//- for sprintf()
#include <string.h>			//- for memset()
#include <math.h>
#include <random>			//- for srand()
#include <time.h>			//- for currentTime (srand)
//#include <vld.h>

//Application header files
#include "RGBColor.h"
#include "PixelDrawer.h"
#include "LineDrawer.h"
#include "GraphicsSettings.h"
#include "ScanLineTriangle.h"
#include "ScanLineTriangleDrawer.h"
#include "Polygon2D.h"
#include "DecompPolygon2D.h"
#include "PolygonDrawer.h"
#include "VJSReader.h"
#include "3DPolygonDrawer.h"
#include "Polygon3DTranslator.h"
#include "World.h"
#include "Polygon3DScaler.h"
#include "Polygon3DRotator.h"
#include "UserInput.h"
#include "Reference3DPolygon.h"
#include "BoundingBox.h"
#include "BoundingBoxDrawer.h"
#include "ZBuffer.h"
#include "ExplodedPolygon.h"
#include "ExplodedPolygonAnimator.h"
#include "ExplodedPolygonCreator.h"
#include "ExplodedPolygonManager.h"
#include "PolygonDatabase.h"
#include "Polygon3DFactory.h"
#include "Polygon3DManager.h"
#include "Game.h"
#include "StatusDisplay.h"
#include "ScoreStatusItem.h"
#include "MissedPolygonStatusItem.h"
#include "GameOverStatusItem.h"
#include "HighScoreStatusItem.h"


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
const std::string VJS_INDEX = "POLYGON_INDEX.TXT";
//====== Structs & typedefs =========
typedef unsigned char BYTE;



//====== Global Variables ==========
BYTE	pFrameL[FRAME_WIDE * FRAME_HIGH * 3];
BYTE	pFrameR[FRAME_WIDE * FRAME_HIGH * 3];
int		NUM_CHANNELS = 3;
int		shade = 0;

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

	// -- load VJS polygons from command line --	
	PolygonDatabase *d = PolygonDatabase::getSingleton();
	int numPolysLoaded = 0;
	std::vector<std::string> vjsFiles = VJSReader::readIndexFile(VJS_INDEX);
	unsigned int numFiles = vjsFiles.size();
	for (int i = 0; i < numFiles; i++)
	{			
		if (d->loadPolygonAtPath(vjsFiles[i]))
			numPolysLoaded++;
	}
	if (numPolysLoaded == 0) return EXIT_FAILURE; //End program if no polygons

	// -- setup world -- 
 	GraphicsSettings* settings = GraphicsSettings::getGraphicsSettings();
	settings->setFrameDimensions(FRAME_WIDE, FRAME_HIGH);
	settings->setNumberOfChannels(NUM_CHANNELS);
	settings->setView(0);
	settings->setFOV(1000);
	settings->setSecondFrame(false);
	Game *game = Game::getSingleton();
	game->setStatus(GSTATUS_RUNNING);
	StatusDisplay *display = StatusDisplay::getSingleton();
	display->addStatusItem(new ScoreStatusItem());
	display->addStatusItem(new MissedPolygonStatusItem());
	display->addStatusItem(new GameOverStatusItem());
	display->addStatusItem(new HighScoreStatusItem());

	// -- Seed the random number generator
	srand(time(NULL));
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
	glRasterPos2i(200, 200);
	StatusDisplay::getSingleton()->draw();
	
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
	UserInput::getSingleton()->handleMouseInput(button, state, x, y);
}

void OnKeypress(unsigned char key, int x, int y)
{


	switch (key) 
	{ 	
		case '3': stereo ^= 1, eyes = 10;break;
		case ']': eyes++;	break;
		case '[': eyes--;	break;
		case 27 : exit(0);
		default:
		{
			UserInput::getSingleton()->handleKeyInput(key);
		}

	}

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
		GraphicsSettings::getGraphicsSettings()->setSecondFrame(true);
		BuildFrame(pFrameR, +eyes);
		GraphicsSettings::getGraphicsSettings()->setSecondFrame(false);
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
	GraphicsSettings* gSettings = GraphicsSettings::getGraphicsSettings();
	gSettings->setFrameBuffer(screen);
	gSettings->setView(view);
	World *world = World::getSingleton();
	if (Game::getSingleton()->getCurrentStatus() == GSTATUS_RUNNING)
		world->drawWorld();
	StatusDisplay::getSingleton()->draw();

}





