#include <math.h>

#include "DecompPolygon2D.h"
#include <algorithm>

#ifdef _WIN32
	#include <windows.h>
#endif

DecompPolygon2D::DecompPolygon2D(Polygon2D* p)
{
	this->numSides = p->numSides;
	this->sides = p->sides;
	this->decompSides.assign(sides.begin(), sides.end());
	this->triangles.reserve(p->numSides - 2);
	decompose();
}


void DecompPolygon2D::decompose()
{
	RGBColour* c = (RGBColour*)malloc(sizeof(RGBColour));
	c->red = c->green = c->blue = 255;
	GPLine* connectingLine;
	for (int i = 0; i < numSides - 2; i++)
	{
		int leftLineInd = findLeftMostLineIndex();
		int adjLineInd = findAdjacentLineIndex(leftLineInd);
		GPLine* connLine = createConnectingLine(decompSides[leftLineInd], decompSides[adjLineInd]);
		//Check every point for intersections
		for (int j = 0; decompSides.size() > 3 && j < decompSides.size(); j++)
		{
			if (!(j == leftLineInd || j == adjLineInd || decompSides[j] == NULL))
			{
				int result = insideTest(decompSides[leftLineInd], decompSides[adjLineInd],
										connLine, decompSides[j]);
				if (result != 0) //No intersection
				{
					
					

				}
				
			}
		}
		GPLine* a = decompSides[leftLineInd];
		GPLine* b = decompSides[adjLineInd];
		POINT2D pa = { a->x1, a->y1 };
		POINT2D pb = { a->x2, a->y2 };
		POINT2D pc;
		if ((b->x1 == pa.x && b->y1 == pa.y) ||
			(b->x1 == pb.x && b->y1 == pb.y))
		{
			pc.x = b->x2; pc.y = b->y2;
		} else
		{	
			pc.x = b->x1; pc.y = b->y1;
		}
		
		triangles.push_back(new ScanLineTriangle(pa.x, pa.y, pb.x, pb.y,
													pc.x, pc.y,
													c, c, c));
		decompSides.push_back(connLine);
		decompSides.erase(decompSides.begin() + leftLineInd);
		decompSides.erase(decompSides.begin() + adjLineInd - 1);

	}
	

}

//Returns true if point intersects
bool DecompPolygon2D::boxTest(POINT2D pA, POINT2D pB, POINT2D pC, POINT2D pTest)
{
	int leftEdge, rightEdge, topEdge, bottomEdge;
	leftEdge = min(min(pA.x, pB.x), pC.x);
	rightEdge = max(max(pA.x, pB.x), pC.x);
	topEdge = max(max(pA.y, pB.y), pC.y);
	bottomEdge = min(min(pA.y, pB.y), pC.y);
	//Test
	bool outside = false;
	outside = pTest.x < leftEdge || pTest.x > rightEdge;
	outside = outside || pTest.y < bottomEdge || pTest.y > topEdge;	
	
	return !outside;
}

int DecompPolygon2D::insideTest(GPLine* a, GPLine* b, GPLine* c, GPLine* test)
{
	POINT2D pa = { a->x1, a->y1 };
	POINT2D pb = { a->x2, a->y2 };
	POINT2D pc, ptest;
	if ((b->x1 == pa.x && b->y1 == pa.y) ||
		(b->x1 == pb.x && b->y1 == pb.y))
	{
		pc.x = b->x2; pc.y = b->y2;
	} else
	{	
		pc.x = b->x1; pc.y = b->y1;
	}
	//Test X1Y1 then X2Y2
	ptest.x = test->x1; ptest.y = test->y1;
	if (insideTest(pa, pb, pc, ptest))
		return 1; 
	ptest.x = test->x2; ptest.y = test->y2;
	if (insideTest(pa, pb, pc, ptest))
		return 2; 
	else return 0;
}

bool DecompPolygon2D::insideTest(POINT2D pA, POINT2D pB, POINT2D pC, POINT2D pTest)
{
	if (!boxTest(pA, pB, pC, pTest)) 
		return true;
	else
		return sameSide(pA, pB, pC, pTest) &&
				sameSide(pA, pC, pB, pTest) &&
				sameSide(pB, pC, pA, pTest);
}

bool DecompPolygon2D::sameSide(POINT2D l1, POINT2D l2, POINT2D pA, POINT2D pB)
{
	double apt = (l2.x - l1.x) * (pA.y - l1.y) - (l2.y - l1.y) * (pA.x - l1.x);
	double bpt = (l2.x - l1.x) * (pB.y - l1.y) - (l2.y - l1.y) * (pB.x - l1.x);
	//int apt = (pA.x-l1.x) * (l2.y-l1.y) - (l2.x-l1.x) * (pA.y-l1.y);
	//int bpt = (pB.x-l1.x) * (l2.y-l1.y) - (l2.x-l1.x) * (pB.y- l1.y);
	return ((apt * bpt) > 0);
}

bool DecompPolygon2D::compare(GPLine* a, GPLine* b)
{
	if (a == NULL) return false;
	if (b == NULL) return true;
	if ((a->x1 < b->x1 && a->x1 < b->x2) ||
		(a->x2 < b->x1 && a->x2 < b->x2))
		return true;
	else
		return false;
}

int DecompPolygon2D::findLeftMostLineIndex()
{
	std::sort(decompSides.begin(), decompSides.end(), compare);
	int size = decompSides.size();
	int i = 0;
	while (i < size && decompSides[i] == NULL)
		i++;
	return i;
}

int DecompPolygon2D::findAdjacentLineIndex(int lineAInd)
{
	//Get minimum x value x,y pair
	int x, y;
	GPLine* lineA = decompSides[lineAInd];
	x = min(lineA->x1, lineA->x2); 
	if (x == lineA->x1) 
		y = lineA->y1;
	else
		y = lineA->y2;
	//Find first line with equal pair that != lineAInd
	GPLine* cmp;
	int size = decompSides.size();
	for (int i = 0; i < size; i++)
	{
		if (i != lineAInd && decompSides[i] != NULL)
		{
			cmp = decompSides[i];
			if ((cmp->x1 == x && cmp->y1 == y) ||
				(cmp->x2 == x && cmp->y2 == y))
				return i;
		}
	}
	return -1;
}

GPLine* DecompPolygon2D::createConnectingLine(GPLine* a, GPLine* b)
{
	POINT2D common, aPoint, bPoint;
	//Find 2 points that are not in both lines
	if ( (a->x1 == b->x1 && a->y1 == b->y1) ||
		 (a->x1 == b->x2 && a->y1 == b->y2))
	{
		common.x = a->x1; common.y = a->y1;
		aPoint.x = a->x2; aPoint.y = a->y2;
	} else
	{
		common.x = a->x2; common.y = a->y2;
		aPoint.x = a->x1; aPoint.y = a->y1;
	}
	if ( !(b->x1 == common.x && b->y1 == common.y) )
	{
		bPoint.x = b->x1; bPoint.y = b->y1;
	} else
	{
		bPoint.x = b->x2; bPoint.y = b->y2;
	}
	return new GPLine(aPoint.x, aPoint.y, bPoint.x, bPoint.y);
}
