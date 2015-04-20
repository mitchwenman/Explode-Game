#ifndef VJSREADER_
#define VJSREADER_

#include "Polygon3D.h"
#include <vector>

namespace VJSReader
{
	/******************
	Description:Reads a VJS file and creates a polygon from it
	Parameters: string fileName: The path to the VJS file
	Preconditions: fileName exists and is a valid VJS file.
	Postconditions: NIL
	Returns:  The created polygon from the VJS file.
	*******************/
	Polygon3D* read(std::string fileName);

	/******************
	Description:Reads a polygon index file and returns the list of VJS files contained in it
	Parameters: string fileName: The path to the VJS file
	Preconditions: fileName exists and is a valid VJS index file.
	Postconditions: NIL
	Returns:  The list of VJS file names.
	*******************/
	std::vector<std::string> readIndexFile(std::string filename);

}

#endif