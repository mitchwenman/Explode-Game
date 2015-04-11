#include "VJSReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

Polygon3D* VJSReader::read(string fileName)
	{
		try
		{
			Polygon3D* p = new Polygon3D();
			ifstream infile;
			string line;
			int numVerts, numPolys;

			infile.open(fileName);
			if (!infile.is_open()) return NULL;
		
			while (true)
			{
				if (!getline(infile, line)) return NULL;
				if (line.at(0) != '/') break;
			}
		
			stringstream linecpy(line);
			//Get numverts, numpolys		
			string verts, polys;
			getline(linecpy, verts, ',');
			getline(linecpy, polys);
			numVerts = stoi(verts);
			numPolys = stoi(polys);

			while (true) //Read until vertexes
			{
				if (!getline(infile, line)) return NULL;
				if (!line.empty() && line.at(0) != '/') break;
			}
			for (int i = 0; i < numVerts; i++)
			{
				int x, y, z, r, g, b;
				stringstream linecpy(line);
				string elements[6];
				for (int j = 0; j < 6; j++)
				{
					string s;
					getline(linecpy, s, ' ');
					while (s.empty())
					{
						getline(linecpy, s, ' ');
					}
					elements[j] = s;
				}
				x = stoi(elements[0]);
				y = stoi(elements[1]);
				z = stoi(elements[2]);
				r = stoi(elements[3]);
				g = stoi(elements[4]);
				b = stoi(elements[5]);
				VERTEX_3D v;
				v.x = x; v.y = y; v.z = z;
				RGBColour* c = new RGBColour();
				c->red = r; c->green = g; c->blue = b;
				v.c = c;
				p->vertices.push_back(v);	
				getline(infile, line);
			}
			while (true) //Read until polys
			{
				if (!getline(infile, line)) return NULL;
				if (!line.empty() && line.at(0) != '/') break;
			}
			p->polygons.reserve(numPolys);
			for (int i = 0; i < numPolys; i++)
			{			
				stringstream linecpy(line);			
				string s;
				getline(linecpy, s, ' ');
				while (s.empty())
				{
					getline(linecpy, s, ' ');
				}
				vector<int> vList;
				int j = 0;
				do 
				{
					if (j == 0)
					{
						j++; //ignore first number (number of vertices)
						getline(linecpy, s, ' ');
					}
					else
					{
						int vIndex = stoi(s);				
						vList.push_back(vIndex);
						getline(linecpy, s, ' ');
						if (!s.empty() && stoi(s) == vIndex) break;
					}
				
				} while (!s.empty());
				p->polygons.push_back(vList);
				getline(infile, line);			

			}
		
			return p;
		}
		catch (std::invalid_argument e)
		{
			return NULL;
		}
		
	}

	