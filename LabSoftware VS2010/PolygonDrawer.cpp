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
		Polygon2D* cp = clipPolygon2(p, leftEdge, topEdge, rightEdge, bottomEdge);
		if (cp != NULL)
		{
			DecompPolygon2D* d = new DecompPolygon2D(cp);
			for (int i = 0; i < d->triangles.size(); i++)
			{
				ScanLineTriangleDrawer::draw(d->triangles[i]);
			}
		}
		
	}

	Polygon2D* clipPolygon2(Polygon2D* p, int leftEdge, int topEdge, int rightEdge, int bottomEdge)
	{
		//Get vert list from existing edges
		std::vector<GPLine *> inputLines = p->sides;
		std::vector<VERTEX> input, output;
		for (unsigned int i = 0; i < inputLines.size(); i++)
		{
			VERTEX v = { inputLines[i]->x1, inputLines[i]->y1, inputLines[i]->c1 };
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

	std::vector<VERTEX> clipHorizontal(std::vector<VERTEX> input, int boundary, ClipType c)
	{
		std::vector<VERTEX> output;
		for (unsigned int i = 0; i < input.size(); i++)
		{
			VERTEX p1 = input[i];
			VERTEX p2 = input[(i + 1) % input.size()];
			if (c == MIN)
			{
				if (p1.y < boundary && p2.y >= boundary) //1st out, 2nd in
				{

					if (p2.x == p1.x)
					{
						VERTEX intersect = { p1.x, boundary, p1.c };
						output.push_back(intersect);
						output.push_back(p2);
					} else
					{
						int gradient = (p2.y - p1.y)/(p2.x - p1.x);
     						VERTEX intersect = { (boundary - p1.y + gradient * p1.x) / gradient, boundary , p1.c };
						output.push_back(intersect);
						output.push_back(p2);
					}
					
				} else if (p2.y < boundary && p1.y >= boundary) //1st in, 2nd out
				{
					if (p2.x == p1.x)
					{
						VERTEX intersect = { p1.x, boundary, p1.c };
						output.push_back(intersect);
					} else
					{
						int gradient = (p2.y - p1.y)/(p2.x - p1.x);
						VERTEX intersect = { (boundary - p1.y + gradient * p1.x) / gradient, boundary , p2.c };
						output.push_back(intersect);
					}					
				} else if (p1.y >= boundary && p2.y >= boundary) //both in
				{
					output.push_back(p2);
				}
			} else 
			{
				if (p1.y > boundary && p2.y <= boundary) //1st out, 2nd in
				{

					if (p2.x == p1.x)
					{
						VERTEX intersect = { p1.x, boundary, p1.c };
						output.push_back(intersect);
						output.push_back(p2);
					} else
					{
						int gradient = (p2.y - p1.y)/(p2.x - p1.x);
						VERTEX intersect = { (boundary - p1.y + gradient * p1.x) / gradient, boundary , p1.c };
						output.push_back(intersect);
						output.push_back(p2);
					}
					
				} else if (p2.y > boundary && p1.y <= boundary) //1st in, 2nd out
				{
					if (p2.x == p1.x)
					{
						VERTEX intersect = { p1.x, boundary, p1.c };
						output.push_back(intersect);
					} else
					{
						int gradient = (p2.y - p1.y)/(p2.x - p1.x);
						VERTEX intersect = { (boundary - p1.y + gradient * p1.x) / gradient, boundary , p2.c };
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

	std::vector<VERTEX> clipVertical(std::vector<VERTEX> input, int boundary, ClipType c)
	{
		std::vector<VERTEX> output;
		for (unsigned int i = 0; i < input.size(); i++)
		{
			VERTEX p1 = input[i];
			VERTEX p2 = input[(i + 1) % input.size()];
			if (c == MIN)
			{
				if (p1.x < boundary && p2.x >= boundary) //1st out, 2nd in
				{
					double gradient = (p2.y - p1.y)/(p2.x - p1.x);
					int b = p1.y - gradient * p1.x;
					VERTEX intersect = { boundary, gradient * boundary + b, p1.c };
					output.push_back(intersect);
					output.push_back(p2);
				} else if (p2.x < boundary && p1.x >= boundary) //1st in, 2nd out
				{
					double gradient = (p2.y - p1.y)/(p2.x - p1.x);
					int b = p2.y - gradient * p2.x;
					VERTEX intersect = { boundary, gradient * boundary + b, p2.c };
					output.push_back(intersect);
				} else if (p1.x >= boundary && p2.x >= boundary)
				{
					output.push_back(p2);
				}
			} else 
			{
				if (p1.x >= boundary && p2.x < boundary) //1st out, 2nd in
				{
					double gradient = (p2.y - p1.y)/(p2.x - p1.x);
					int b = p1.y - gradient * p1.x;
					VERTEX intersect = { boundary - 1, gradient * (boundary - 1) + b, p1.c };
					output.push_back(intersect);
					output.push_back(p2);
				} else if (p2.x >= boundary && p1.x < boundary) //1st in, 2nd out
				{
					double gradient = (p2.y - p1.y)/(p2.x - p1.x);
					int b = p2.y - gradient * p2.x;
					VERTEX intersect = { boundary - 1, gradient * (boundary - 1) + b, p2.c };
					output.push_back(intersect);
				} else if (p1.x < boundary && p2.x < boundary)
				{
					output.push_back(p2);
				}
			}
			
		}
		return output;
	}

	Polygon2D* clipPolygon(Polygon2D* p)
	{
		std::vector<GPLine*> oldSides = p->sides;
		std::vector<VERTEX> newVerts;
		for (int i = 0; i < oldSides.size(); i++)
		{
			GPLine* old = oldSides[i];
			if (LineDrawer::lineNeedsClipping(old))
			{
				GPLine* nl = LineDrawer::clipLine(old);
				if (nl != NULL) 
				{
					//1st inside, 2nd outside
					if (nl->x1 == old->x1 && nl->y1 == old->y1 &&
						(nl->x2 != old->x2 || nl->y2 != old->y2))
					{
						VERTEX p = { nl->x2, nl->y2, nl->c2 };
						newVerts.push_back(p);
					} else if ((nl->x1 != old->x1 || nl->y1 != old->y1) && //2nd inside, 1st outside
								(nl->x2 == old->x2 || nl->y2 == old->y2))
					{
						VERTEX p1 = { nl->x1, nl->y1, nl->c1 };
						VERTEX p2 = { nl->x2, nl->y2, nl->c2 };
						newVerts.push_back(p1);
						newVerts.push_back(p2);
					} else
					{
						VERTEX p1 = { nl->x1, nl->y1, nl->c1 };
						VERTEX p2 = { nl->x2, nl->y2, nl->c2 };
						newVerts.push_back(p1);
						newVerts.push_back(p2);
					}
				}
			} else //Both inside
			{
				VERTEX p2 = { old->x2, old->y2, old->c2 };
				newVerts.push_back(p2);
			}
		}
		if (newVerts.size() > 0)
			return new Polygon2D(newVerts.size(), newVerts.data()); 
		else
			return NULL;
	}
}