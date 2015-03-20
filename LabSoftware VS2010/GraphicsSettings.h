#ifndef GRAPHICSSETTINGS_
#define GRAPHICSSETTINGS_

#include "RGBColor.h"

class GraphicsSettings
{

private:
	int frameWidth, frameHeight;
	int view;
	int numberOfChannels;

	BYTE* frameBuffer;


	GraphicsSettings();

public:
	void setFrameDimensions(int width, int height);
	
	void setNumberOfChannels(int n);
	void setFrameBuffer(BYTE* buffer);
	void setView(int view);

	int getFrameWidth() { return frameWidth; }
	int getFrameHeight() { return frameHeight; }
	int getNumberOfChannels() { return numberOfChannels; }
	int getView() { return view; }

	BYTE* getFrameBuffer() { return frameBuffer; }
	
	static GraphicsSettings* getGraphicsSettings();

	


};

#endif