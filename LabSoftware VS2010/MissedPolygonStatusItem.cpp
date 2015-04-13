#include "MissedPolygonStatusItem.h"
#include "Game.h"


void MissedPolygonStatusItem::draw()
{
	Game* game = Game::getSingleton();
	int numMissedPolygons =  game->getNumberOfMissedPolygons();
	
}