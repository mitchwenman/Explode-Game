#pragma once

/*
 Reward sound effect created by: Cabeeno Rossley
 Available here: http://www.freesound.org/people/Cabeeno%20Rossley/

 Creative Commons License: http://creativecommons.org/licenses/by/3.0/legalcode
 */



namespace SoundEffect
{
	/******************
	Description:Plays the sound file at the given path.
	Parameters: char* filename: The path to the sound file.
	Preconditions: Input param not null.
	Postconditions: NIL
	Returns:  void
	*******************/
	void playSound(char* filename);

	/******************
	Description:Plays the sound played when a polygon is hit.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void playPolygonHitSoundEffect();

	/******************
	Description:Plays the sound played when the user clicks but misses a polygon.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void playClickSoundEffect();

	/******************
	Description:Plays the sound played when the user's score eclipses the current high score.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void playRewardSoundEffect();

	/******************
	Description:Plays the sound played when the game is over.
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  void
	*******************/
	void playGameOverSoundEffect();
}