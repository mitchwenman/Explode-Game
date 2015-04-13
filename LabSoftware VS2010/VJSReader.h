#ifndef VJSREADER_
#define VJSREADER_

#include "Polygon3D.h"
#include <vector>

namespace VJSReader
{
	//Reads a VJS file and creates a polygon from it
	Polygon3D* read(std::string fileName);

	//Reads a VJS index file and returns a vector of filenames
	std::vector<std::string> readIndexFile(std::string filename);

}

#endif