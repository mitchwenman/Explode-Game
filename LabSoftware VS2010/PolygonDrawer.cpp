#include "PolygonDrawer.h"
#include "DecompPolygon2D.h"
#include "ScanLineTriangleDrawer.h"
#include "GPLine.h"
#include "LineDrawer.h"

#include <vector>

namespace PolygonDrawer
{
	void draw(Polygon2D* p)
	{
		Polygon2D* cp = clipPolygon(p);
		DecompPolygon2D* d = new DecompPolygon2D(cp);
		for (int i = 0; i < d->triangles.size(); i++)
		{
			ScanLineTriangleDrawer::draw(d->triangles[i]);
		}
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
						VERTEX p2 = { nl->x2, nl->y2, nl->c1 };
						newVerts.push_back(p1);
						newVerts.push_back(p2);
					} else
					{
						VERTEX p1 = { nl->x1, nl->y1, nl->c1 };
						VERTEX p2 = { nl->x2, nl->y2, nl->c1 };
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
		return new Polygon2D(newVerts.size(), newVerts.data()); 
	}
}