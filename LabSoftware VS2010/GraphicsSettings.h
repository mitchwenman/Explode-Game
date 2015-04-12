#ifndef GRAPHICSSETTINGS_
#define GRAPHICSSETTINGS_

#include "RGBColor.h"

#define MIN_Z_RENDER -500 
#define MAX_Z_RENDER 5000


class GraphicsSettings
{

private:
	int		frameWidth, frameHeight;
	int		view;
	int		fov;
	int		numberOfChannels;

	BYTE*	frameBuffer;

	//Whether we're rendering the second frame now (in stereo)
	bool	secondFrame;


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

	//Returns whether we're rendering the second frame
	bool isSecondFrame() { return secondFrame; }

	//Sets whether we're rendering the second frame
	void setSecondFrame(bool b) { secondFrame = b; }

	
	//Returns the graphic settings singleton object
	static GraphicsSettings* getGraphicsSettings();

	


};

#endif