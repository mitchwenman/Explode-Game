#include "SoundEffect.h"
#include <stdlib.h>

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

namespace SoundEffect
{
	void playSound(char* filename)
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

	void playPolygonHitSoundEffect()
	{
		playSound("EXPLOSION.WAV");
	}

	void playClickSoundEffect()
	{
		playSound("WHOOSH.WAV");
	}
}