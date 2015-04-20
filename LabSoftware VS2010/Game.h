#pragma once

#include <string>

typedef enum { GSTATUS_RUNNING, GSTATUS_OVER } GameStatus;


class Game
{

private:
	static const int DEFAULT_SCORE_INCREMENT = 100;

	/******************
	Description: Private constructor for singleton pattern
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: 
	*******************/
	Game() : score(0), missedPolygons(0), nextScoreIncrement(DEFAULT_SCORE_INCREMENT), highScore(0) {};

	//The current score
	int score;

	//The next amount to be added to the score
	int nextScoreIncrement;

	//The current status of the game
	GameStatus currentStatus;

	//The number of missed polygons
	int missedPolygons;

public:
	int highScore;

	//The maximum number of missed polygons before the game ends
	static const int MAX_MISSED_POLYGONS = 5;

	/******************
	Description: Creates if necessary and returns the singleton object.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: The singleton Game* instance.
	*******************///
	static Game* getSingleton();

	/******************
	Description: Sets the game status. If game is over, destroys all polygons.
	Parameters: GameStatus newstatus: The new game status.
	Preconditions: NIL
	Postconditions: If game was running and is now over, all exploded polygons and 3d polygons will be destroyed.
	Returns: void
	*******************/
	void setStatus(GameStatus newStatus);

	//Gets the current game status
	GameStatus getCurrentStatus() { return currentStatus; }

	//Returns the score of the game
	int getScore() { return score; }

	/******************
	Description: Increments the score by an increasing amount. Sets the high score if above.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns: The new score.
	*******************///
	int incrementScore();

	/******************
	Description: Increments the total missed polygons.
	Parameters: int n: The number to increment the total by.
	Preconditions: NIL
	Postconditions: Game status may change to over if over missed poly limit.
	Returns: the number of missed polygons.
	*******************/
	int incrementMissedPolygons(int n = 1);
	
	//Returns the number of missed polygons
	int getNumberOfMissedPolygons() { return missedPolygons; }
};