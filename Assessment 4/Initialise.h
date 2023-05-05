#pragma once

// Set the parameters for the game to run after starting and before ending

class Initialise
{

private:
	// private stuff here (C++ classes are private by default)

public: 
	// The default constuctor function fires once on instantiation, so this is an ideal place to set the startig conditions of the game.
	Initialise() 
	{
		/* 1: GAME PARAMETERS
		1.1: Starting conditions
		Set the parameters for the game to run after starting and before ending
			1.1.1: Create the visible play area
			1.1.2: Create a timer
			1.1.3: Create and set player score = 0
			1.1.4 Set target FPS

		1.2: Win/loss conditions
			1.2.1: Win if enemy lives = 0
			1.2.2: Lose of player lives = 0

		1.3: Objects
			1.3.1: Instantiate the player
				1.3.1.1: Set initial position
				1.3.1.2: Offset the player object to the middle of its object rather than top left
				1.3.1.3: set size of the offset for collision detection?
				1.3.1.4: Set lives = 1
				1.3.1.5: Instantiate the player's sprite as a child

			1.3.2: Instantiate enemies
				1.3.2.1: Set initial position
				1.3.2.2: Offset the enemy object to the middle of its object rather than top left
				1.3.2.3: set size of the offset for collision detection?
				1.3.2.4: Instantiate sprites

			1.3.3: Instantiate the base
				1.3.3.1: Set position
				1.3.3.2: Set lives = 1
				1.3.3.3: Set position
				1.3.3.4: Instantiate sprites

	*/
	};

	// default destructor function
	~Initialise();
};

