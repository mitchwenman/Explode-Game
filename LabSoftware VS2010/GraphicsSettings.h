#ifndef GRAPHICSSETTINGS_
#define GRAPHICSSETTINGS_

#include "RGBColor.h"

class GraphicsSettings
{

private:
	int frameWidth, frameHeight;
	
	int numberOfChannels;

	BYTE* frameBuffer;


	GraphicsSettings();

public:
	void setFrameDimensions(int width, int height);
	
	void setNumberOfChannels(int n);
	void setFrameBuffer(BYTE* buffer);

	int getFrameWidth() { return frameWidth; }
	int getFrameHeight() { return frameHeight; }
	int getNumberOfChannels() { return numberOfChannels; }

	BYTE* getFrameBuffer() { return frameBuffer; }
	
	static GraphicsSettings* getGraphicsSettings();

	


};

#endif