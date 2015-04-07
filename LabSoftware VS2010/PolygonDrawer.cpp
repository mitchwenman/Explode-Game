#include "PolygonDrawer.h"
#include "DecompPolygon2D.h"
#include "ScanLineTriangleDrawer.h"
#include "GPLine.h"
#include "LineDrawer.h"
#include "GraphicsSettings.h"

#include <vector>

namespace PolygonDrawer
{
	void draw(Polygon2D* p)
	{
		GraphicsSettings *g = GraphicsSettings::getGraphicsSettings();
		int topEdge = g->getFrameHeight();
		int rightEdge = g->getFrameWidth();
		int leftEdge, bottomEdge;
		leftEdge = bottomEdge = 0;
		Polygon2D* cp = clipPolygon(p, leftEdge, topEdge, rightEdge, bottomEdge);
		if (cp != NULL)
		{
			DecompPolygon2D* d = new DecompPolygon2D(cp);
			for (int i = 0; i < d->triangles.size(); i++)
			{
				ScanLineTriangleDrawer::draw(d->triangles[i]);
			}
		}
		
	}

	Polygon2D* clipPolygon(Polygon2D* p, int leftEdge, int topEdge, int rightEdge, int bottomEdge)
	{
		//Get vert list from existing edges
		std::vector<GPLine *> inputLines = p->sides;
		std::vector<VERTEX_3D> input, output;
		for (unsigned int i = 0; i < inputLines.size(); i++)
		{
			VERTEX_3D v = { inputLines[i]->x1, inputLines[i]->y1, inputLines[i]->z1, inputLines[i]->c1 };
			input.push_back(v);
		}
		
		//Get vert list from left edge
		output = clipVertical(input, leftEdge, MIN);
		input = output;
		//Top edge
		input = output = clipHorizontal(input, topEdge, MAX);
		
		//Right edge
		input = output = clipVertical(input, rightEdge, MAX);
		//bottom edge
		output = clipHorizontal(input, bottomEdge, MIN);
		if (output.size() > 0)
			return new Polygon2D(output.size(), output.data());
		else 
			return NULL;
	}

	std::vector<VERTEX_3D > clipHorizontal(std::vector<VERTEX_3D> input, int boundary, ClipType c)
	{
		std::vector<VERTEX_3D> output;
		for (unsigned int i = 0; i < input.size(); i++)
		{
			VERTEX_3D p1 = input[i];
			VERTEX_3D p2 = input[(i + 1) % input.size()];
			if (c == MIN) //Outside points less than boundary
			{
				if (p1.y < boundary && p2.y >= boundary) //1st out, 2nd in
				{
					int newZ = p1.z + (p1.z - p2.z) * (abs(p1.y) /((double)(p2.y - p1.y)));
					if (p2.x == p1.x)
					{
						VERTEX_3D intersect = { p1.x, boundary, newZ , p1.c };
						output.push_back(intersect);
						output.push_back(p2);
					} else
					{
						double gradient = (p2.y - p1.y)/(double)(p2.x - p1.x);
						double b = p1.y - gradient * p1.x;
     					VERTEX_3D intersect = { (boundary - b) / gradient, boundary, newZ, p1.c };
						output.push_back(intersect);
						output.push_back(p2);
					}
					
				} else if (p2.y < boundary && p1.y >= boundary) //1st in, 2nd out
				{
					int newZ = p2.z + (p1.z - p2.z) * (abs(p2.y) /((double)(p1.y - p2.y)));
					if (p2.x == p1.x)
					{
						VERTEX_3D intersect = { p1.x, boundary, newZ, p1.c };
						output.push_back(intersect);
					} else
					{
						double gradient = (p2.y - p1.y)/(double)(p2.x - p1.x);
						double b = p2.y - gradient * p2.x;
						VERTEX_3D intersect = { (boundary - b) / gradient, boundary, newZ, p2.c };
						output.push_back(intersect);
					}					
				} else if (p1.y >= boundary && p2.y >= boundary) //both in
				{
					output.push_back(p2);
				}
			} else //Outside points greater than boundary
			{
				if (p1.y > boundary && p2.y <= boundary) //1st out, 2nd in
				{
					int newZ = p1.z + (p1.z - p2.z) * ((p1.y - boundary) /((double)(p1.y - p2.y)));
					if (p2.x == p1.x)
					{
						VERTEX_3D intersect = { p1.x, boundary - 1, newZ, p1.c };
						output.push_back(intersect);
						output.push_back(p2);
					} else
					{
						double gradient = (p2.y - p1.y)/(double)(p2.x - p1.x);
						double b = p1.y - gradient * p1.x;
						VERTEX_3D intersect = { (boundary - b) / gradient, boundary - 1, newZ, p1.c };
						output.push_back(intersect);
						output.push_back(p2);
					}
					
				} else if (p2.y > boundary && p1.y <= boundary) //1st in, 2nd out
				{
					int newZ = p2.z + (p1.z - p2.z) * ((p2.y - boundary) /((double)(p2.y - p1.y)));
					if (p2.x == p1.x)
					{						
						VERTEX_3D intersect = { p1.x, boundary - 1, newZ, p1.c };
						output.push_back(intersect);
					} else
					{
						double gradient = (p2.y - p1.y)/(double)(p2.x - p1.x);
						double b = p2.y - gradient * p2.x;
						VERTEX_3D intersect = { (boundary - b) / gradient, boundary - 1 , newZ, p2.c };
						output.push_back(intersect);
					}					
				} else if (p1.y <= boundary && p2.y <= boundary)
				{
					output.push_back(p2);
				}
			}
			
		}
		return output;
	}

	std::vector<VERTEX_3D> clipVertical(std::vector<VERTEX_3D> input, int boundary, ClipType c)
	{
		std::vector<VERTEX_3D> output;
		for (unsigned int i = 0; i < input.size(); i++)
		{
			VERTEX_3D p1 = input[i];
			VERTEX_3D p2 = input[(i + 1) % input.size()];
			if (c == MIN) //Outside points are less than the boundary
			{

				if (p1.x < boundary && p2.x >= boundary) //1st out, 2nd in
				{
					int newZ = p1.z + (p2.z - p1.z) * (p1.x /((double)(p2.x - p1.x)));
					double gradient = (p2.y - p1.y)/(double)(p2.x - p1.x);
					double b = p1.y - gradient * p1.x;
					VERTEX_3D intersect = { boundary, gradient * boundary + b, newZ, p1.c };
					output.push_back(intersect);
					output.push_back(p2);
				} else if (p2.x < boundary && p1.x >= boundary) //1st in, 2nd out
				{
					int newZ = p2.z + (p2.z - p1.z) * (p2.x /((double)(p1.x - p2.x)));
					double gradient = (p2.y - p1.y)/(double)(p2.x - p1.x);
					double b = p2.y - gradient * p2.x;
					VERTEX_3D intersect = { boundary, gradient * boundary + b, newZ, p2.c };
					output.push_back(intersect);
				} else if (p1.x >= boundary && p2.x >= boundary)
				{
					output.push_back(p2);
				}
			} else //Outside points are greater than the boundary
			{
				if (p1.x >= boundary && p2.x < boundary) //1st out, 2nd in
				{
					int newZ = p1.z + (p2.z - p1.z) * ((p1.x - boundary) /((double)(p1.x - p2.x)));
					double gradient = (p2.y - p1.y)/(double)(p2.x - p1.x);
					double b = p1.y - gradient * p1.x;
					VERTEX_3D intersect = { boundary - 1, gradient * (boundary - 1) + b, newZ, p1.c };
					output.push_back(intersect);
					output.push_back(p2);
				} else if (p2.x >= boundary && p1.x < boundary) //1st in, 2nd out
				{
					int newZ = p2.z + (p2.z - p1.z) * ((p2.x - boundary) /((double)(p2.x - p1.x)));
					double gradient = (p2.y - p1.y)/(double)(p2.x - p1.x);
					double b = p2.y - gradient * p2.x;
					VERTEX_3D intersect = { boundary - 1, gradient * (boundary - 1) + b, newZ, p2.c };
					output.push_back(intersect);
				} else if (p1.x < boundary && p2.x < boundary)
				{
					output.push_back(p2);
				}
			}
			
		}
		return output;
	}


}