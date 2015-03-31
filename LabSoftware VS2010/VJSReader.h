#ifndef VJSREADER_
#define VJSREADER_

#include "Polygon3D.h"

namespace VJSReader
{
	//Reads a VJS file and creates a polygon from it
	Polygon3D* read(std::string fileName);
}

#endif