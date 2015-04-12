#include "Game.h"

static Game* _instance;

Game* Game::getSingleton()
{
	if (!_instance)
		_instance = new Game();
	return _instance;
}

void Game::setStatus(GameStatus newStatus)
{
	currentStatus = newStatus;
}

int Game::incrementScore()
{
	score += nextScoreIncrement;
	nextScoreIncrement *= 2;
	return score;
}