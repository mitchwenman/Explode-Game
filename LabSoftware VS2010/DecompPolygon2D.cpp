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

bool findCommonPoint(GPLine* a, GPLine* b, VERTEX* common)
{
	if ( (a->x1 == b->x1 && a->y1 == b->y1) ||
		 (a->x1 == b->x2 && a->y1 == b->y2))
	{
		common->x = a->x1; common->y = a->y1; common->c = a->c1;
	} else
	{
		common->x = a->x2; common->y = a->y2; common->c = a->c2;
	}
	return true;
}

//Returns b's non intersecting point with line A
bool findUncommonPoint(GPLine* a, GPLine*b, VERTEX* ucB)
{
	VERTEX common, aPoint, bPoint;
	findCommonPoint(a, b, &common);	
	if (b->x1 == common.x && b->y1 == common.y)
	{
		ucB->x = b->x2; ucB->y = b->y2; ucB->c = b->c2;
	} else
	{
		ucB->x = b->x1; ucB->y = b->y1; ucB->c = b->c1;
	}
	return true;
}

int DecompPolygon2D::findLineWithCoords(VERTEX p1, VERTEX p2)
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

	GPLine* connectingLine;
	int limit = numSides - 2;
	for (int i = 0; i < limit; i++)
	{
		int leftLineInd = findLeftMostLineIndex();
		
		VERTEX pa = { decompSides[leftLineInd]->x1, decompSides[leftLineInd]->y1, decompSides[leftLineInd]->c1 };
		VERTEX pb = { decompSides[leftLineInd]->x2, decompSides[leftLineInd]->y2, decompSides[leftLineInd]->c2 };
		VERTEX pvar;

			int adjLine = findAdjacentLineIndex(leftLineInd);
			if (adjLine == -1) return;
			findUncommonPoint(decompSides[leftLineInd], decompSides[adjLine], &pvar);
			
		
		if (decompSides.size() == 1)
		{
			pvar.x = pa.x; pvar.y = pa.y; pvar.c = pa.c;
		}
		//Check every point for intersections
		for (int j = 0; j < decompSides.size(); j++)
		{
			if (j != leftLineInd && j != adjLine)
			{
				GPLine* test = decompSides[j];
				VERTEX pInside = { test->x1, test->y1, test->c1 }; //Testing if ptest is inside
				if (pvar.x > min(pa.x, pb.x) &&
					!((pInside.x == pa.x && pInside.y == pa.y) ||
						(pInside.x == pb.x && pInside.y == pb.y) ||
						(pInside.x == pvar.x && pInside.y == pvar.y)))
				{
					if (insideTest(pa, pb, pvar, pInside)) //If inside then set inside as pvar and run whole test again
					{					
						pvar.x = pInside.x; pvar.y = pInside.y; pvar.c = pInside.c;
						j = -1;
						continue;
					} 
				}
				
				pInside.x = test->x2; pInside.y = test->y2; pInside.c = test->c2;
				if (pvar.x > min(pa.x, pb.x) &&
					!((pInside.x == pa.x && pInside.y == pa.y) ||
						(pInside.x == pb.x && pInside.y == pb.y) ||
						(pInside.x == pvar.x && pInside.y ==pvar.y)))
				{
					if (insideTest(pa, pb, pvar, pInside))
					{
						pvar.x = pInside.x; pvar.y = pInside.y; pvar.c = pInside.c;
						j = -1;
						continue;
					} 
				}
				
			}
			
		}
		decompSides.erase(decompSides.begin() + leftLineInd);
		//Delete line only if it already exists, otherwise add it
		int paPVLine = findLineWithCoords(pa, pvar);
		if (paPVLine != -1)
			decompSides.erase(decompSides.begin() + paPVLine);
		else 
		{}//decompSides.push_back(new GPLine(pa, pvar));
		int pbPVLine = findLineWithCoords(pb, pvar);
		if (pbPVLine != -1)
			decompSides.erase(decompSides.begin() + pbPVLine);
		else
		{}//decompSides.push_back(new GPLine(pb, pvar));
		
		triangles.push_back(new ScanLineTriangle(pa.x , pa.y, pb.x, pb.y, pvar.x, pvar.y, pa.c, pb.c, pvar.c));		
	}
	

}

//Returns true if point intersects
bool DecompPolygon2D::boxTest(VERTEX pA, VERTEX pB, VERTEX pC, VERTEX pTest)
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
	VERTEX pa = { a->x1, a->y1 };
	VERTEX pb = { a->x2, a->y2 };
	VERTEX pc, ptest;
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

bool DecompPolygon2D::insideTest(VERTEX pA, VERTEX pB, VERTEX pC, VERTEX pTest)
{
	if (!boxTest(pA, pB, pC, pTest)) 
		return false;
	else
		return sameSide(pA, pB, pC, pTest) &&
				sameSide(pA, pC, pB, pTest) &&
				sameSide(pB, pC, pA, pTest);
}

bool DecompPolygon2D::sameSide(VERTEX l1, VERTEX l2, VERTEX pA, VERTEX pB)
{
	double apt = (l2.x - l1.x) * (pA.y - l1.y) - (l2.y - l1.y) * (pA.x - l1.x);
	double bpt = (l2.x - l1.x) * (pB.y - l1.y) - (l2.y - l1.y) * (pB.x - l1.x);
	return ((apt * bpt) >= 0);
}

/* a < b if a has minimum x value
   If both have minimum x value then
   a < b if it has highest y value
*/
bool DecompPolygon2D::compare(GPLine* a, GPLine* b)
{
	if (a == NULL) return false;
	if (b == NULL) return true;
	int minax = min(a->x1, a->x2);
	int minbx = min(b->x1, b->x2);
	if (minax < minbx) return true;
	else if (minbx < minax) return false;
	else //equal
	{
		int maxax = max(a->x1, a->x2);
		int maxbx = max(b->x1, b->x2);
		if (maxax < maxbx)
			return true;
		else if (maxax > maxbx)
			return false;	
		else //sort by height
		{
			int maxay = max(a->y1, a->y2);
			int maxby = max(b->y1, b->y2);
			if (maxay < maxby)
				return true;
			else
				return false;
		}
		
	}
	
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
	VERTEX_3D common, aPoint, bPoint;
	//Find 2 points that are not in both lines
	if ( (a->x1 == b->x1 && a->y1 == b->y1) ||
		 (a->x1 == b->x2 && a->y1 == b->y2))
	{
		common.x = a->x1; common.y = a->y1;
		aPoint.x = a->x2; aPoint.y = a->y2; aPoint.c = a->c2;
	} else
	{
		common.x = a->x2; common.y = a->y2;
		aPoint.x = a->x1; aPoint.y = a->y1; aPoint.c = a->c1;
	}
	if ( !(b->x1 == common.x && b->y1 == common.y) )
	{
		bPoint.x = b->x1; bPoint.y = b->y1; bPoint.c = b->c1;
	} else
	{
		bPoint.x = b->x2; bPoint.y = b->y2; bPoint.c = b->c2;
	}
	return new GPLine(aPoint, bPoint);
}
