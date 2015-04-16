#include "Game.h"
#include "Polygon3DManager.h"
#include "ExplodedPolygonManager.h"
#include "SoundEffect.h"

static Game* _instance;

Game* Game::getSingleton()
{
	if (!_instance)
		_instance = new Game();
	return _instance;
}

void Game::setStatus(GameStatus newStatus)
{
	if (currentStatus == GSTATUS_RUNNING &&
		newStatus == GSTATUS_OVER)
	{
		Polygon3DManager::getSingleton()->reset();
		ExplodedPolygonManager::getSingleton()->reset();
	} else if (currentStatus == GSTATUS_OVER &&
		newStatus == GSTATUS_RUNNING)
	{
		score = 0;
		nextScoreIncrement = DEFAULT_SCORE_INCREMENT;
		missedPolygons = 0;
	}
		
	currentStatus = newStatus;
}

int Game::incrementScore()
{
	score += nextScoreIncrement;
	if (score > highScore) highScore = score;
	nextScoreIncrement *= 1.1;
	return score;
}

int Game::incrementMissedPolygons(int n)
{
	missedPolygons += n;
	if (missedPolygons == MAX_MISSED_POLYGONS)
	{
		SoundEffect::playGameOverSoundEffect();
		setStatus(GSTATUS_OVER);
	}
	return missedPolygons;
}