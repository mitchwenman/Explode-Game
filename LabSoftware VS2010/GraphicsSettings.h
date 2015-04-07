#ifndef GRAPHICSSETTINGS_
#define GRAPHICSSETTINGS_

#include "RGBColor.h"

class GraphicsSettings
{

private:
	int frameWidth, frameHeight;
	int view;
	int fov;
	int numberOfChannels;

	BYTE* frameBuffer;


	GraphicsSettings() { };

public:
	
	//Sets the frame dimensions
	void setFrameDimensions(int width, int height) { this->frameWidth = width; this->frameHeight = height; }
	
	//Sets the number of colour channels
	void setNumberOfChannels(int n) { numberOfChannels = n; }

	//Sets the frame buffer that Set pixel uses to draw into
	void setFrameBuffer(BYTE* buffer) { this->frameBuffer = buffer; }

	//Sets the distance between the eyes for 3D rendering
	void setView(int view) { this->view = view; }

	//Sets the fov
	void setFOV(int fov) { this->fov = fov; }

	//Returns the frame width
	int getFrameWidth() { return frameWidth; }

	//Returns the frame height
	int getFrameHeight() { return frameHeight; }

	//Returns the number of colour channels
	int getNumberOfChannels() { return numberOfChannels; }

	//Returns the distance between the eyes
	int getView() { return view; }

	//Returns the FOV
	int getFOV() { return fov; }

	//Returns the frame buffer
	BYTE* getFrameBuffer() { return frameBuffer; }
	
	//Returns the graphic settings singleton object
	static GraphicsSettings* getGraphicsSettings();

	


};

#endif