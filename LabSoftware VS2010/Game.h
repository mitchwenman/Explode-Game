#pragma once

#include <string>

typedef enum { GSTATUS_RUNNING, GSTATUS_OVER } GameStatus;

class Game
{

private:
	//Private constructor for the singleton pattern
	Game() : score(0), missedPolygons(0), nextScoreIncrement(100) {};

	//The current score
	int score;

	//The next amount to be added to the score
	int nextScoreIncrement;

	//The current status of the game
	GameStatus currentStatus;

	//The number of missed polygons
	int missedPolygons;

public:
	//The maximum number of missed polygons before the game ends
	static const int MAX_MISSED_POLYGONS = 5;

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

	//Increments the number of missed polygons
	int incrementMissedPolygons();
	
	//Returns the number of missed polygons
	int getNumberOfMissedPolygons() { return missedPolygons; }
};