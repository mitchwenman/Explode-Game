#pragma once

#include <string>

typedef enum { GSTATUS_RUNNING, GSTATUS_OVER } GameStatus;

class Game
{

private:
	//Private constructor for the singleton pattern
	Game() : score(0), nextScoreIncrement(100) {};

	//The current score
	int score;

	//The next amount to be added to the score
	int nextScoreIncrement;

	//The current status of the game
	GameStatus currentStatus;

public:
	//Returns the game singleton object
	static Game* getSingleton();

	//Sets the status of the game
	void setStatus(GameStatus newStatus);

	//Gets the current game status
	GameStatus getCurrentStatus() { return currentStatus; }

	//Returns the score of the game
	int getScore() { return score; }

	//Increments the score by the next score increment
	//Returns the new score
	int incrementScore();

	
};