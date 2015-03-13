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

bool findCommonPoint(GPLine* a, GPLine* b, POINT2D* common)
{
	if ( (a->x1 == b->x1 && a->y1 == b->y1) ||
		 (a->x1 == b->x2 && a->y1 == b->y2))
	{
		common->x = a->x1; common->y = a->y1;
	} else
	{
		common->x = a->x2; common->y = a->y2;
	}
	return true;
}

bool findUncommonPoint(GPLine* a, GPLine*b, POINT2D* ucB)
{
	POINT2D common, aPoint, bPoint;
	findCommonPoint(a, b, &common);	
	if (b->x1 == common.x && b->y1 == common.y)
	{
		ucB->x = b->x2; ucB->y = b->y2;
	} else
	{
		ucB->x = b->x1; ucB->y = b->y1;
	}
	return true;
}

int DecompPolygon2D::findLineWithCoords(POINT2D p1, POINT2D p2)
{
	for (int i = 0; i < decompSides.size(); i++)
	{
		GPLine* line = decompSides[i];
		if ((line->x1 == p1.x && line->y1 == p1.y &&
			line->x2 == p2.x && line->y2 == p2.y) ||
			(line->x1 == p2.x && line->y1 == p2.y &&
			line->x2 == p1.x && line->y2 == p1.y))
		{
			return i;
		}
	}
	return -1;
}


void DecompPolygon2D::decompose()
{
	RGBColour* c = (RGBColour*)malloc(sizeof(RGBColour));
	c->red = c->green = c->blue = 255;
	GPLine* connectingLine;
	for (int i = 0; i < numSides - 2; i++)
	{
		int leftLineInd = findLeftMostLineIndex();
		
		POINT2D pa = { decompSides[leftLineInd]->x1, decompSides[leftLineInd]->y1 };
		POINT2D pb = { decompSides[leftLineInd]->x2, decompSides[leftLineInd]->y2 };
		POINT2D pvar;
		findUncommonPoint(decompSides[leftLineInd], decompSides[leftLineInd + 1], &pvar);
		//Check every point for intersections
		for (int j = 0; j < decompSides.size(); j++)
		{
			if (j != leftLineInd)
			{
				GPLine* test = decompSides[j];
				POINT2D pInside = { test->x1, test->y1 }; //Testing if ptest is inside
				if (!((pInside.x == pa.x && pInside.y == pa.y) ||
						(pInside.x == pb.x && pInside.y == pb.y) ||
						(pInside.x == pvar.x && pInside.y == pvar.y)))
				{
					if (insideTest(pa, pb, pvar, pInside))
					{					
						pvar.x = pInside.x; pvar.y = pInside.y;
						j = -1;
						continue;
					} 
				}
				
				pInside.x = test->x2; pInside.y = test->y2;
				if (!((pInside.x == pa.x && pInside.y == pa.y) ||
						(pInside.x == pb.x && pInside.y == pb.y) ||
						(pInside.x == pvar.x && pInside.y ==pvar.y)))
				{
					if (insideTest(pa, pb, pvar, pInside))
					{
						pvar.x = test->x1; pvar.y = test->y1;
						j = -1;
						continue;
					} 
				}
				
			}
			
		}
		decompSides.erase(decompSides.begin() + leftLineInd);
		int paPVLine = findLineWithCoords(pa, pvar);
		if (paPVLine != -1)
			decompSides.erase(decompSides.begin() + paPVLine);
		else 
			decompSides.push_back(new GPLine(pa.x , pa.y, pvar.x, pvar.y));
		int pbPVLine = findLineWithCoords(pb, pvar);
		if (pbPVLine != -1)
			decompSides.erase(decompSides.begin() + pbPVLine);
		else
			decompSides.push_back(new GPLine(pb.x, pb.y, pvar.x, pvar.y));
		
		triangles.push_back(new ScanLineTriangle(pa.x , pa.y, pb.x, pb.y, pvar.x, pvar.y, c, c, c));		
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
		return false;
	else
		return sameSide(pA, pB, pC, pTest) &&
				sameSide(pA, pC, pB, pTest) &&
				sameSide(pB, pC, pA, pTest);
}

bool DecompPolygon2D::sameSide(POINT2D l1, POINT2D l2, POINT2D pA, POINT2D pB)
{
	double apt = (l2.x - l1.x) * (pA.y - l1.y) - (l2.y - l1.y) * (pA.x - l1.x);
	double bpt = (l2.x - l1.x) * (pB.y - l1.y) - (l2.y - l1.y) * (pB.x - l1.x);
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
