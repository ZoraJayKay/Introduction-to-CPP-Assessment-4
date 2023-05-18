#pragma once
#include <iostream>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "SpriteObject.h"

using namespace std;

// Set the parameters for the game to run after starting and before ending

class Initialise
{

private:



public:
	// public pointers that other classes can access
	Player* playerObject;
	Enemy* EnemyPtr;
	vector<Enemy*> EnemyPtrs;

	// File path variables
	const char* playerShipFileName;
	const char* enemyShipFileName;
	const char* baseFileName;

	Initialise();
	/* 1: GAME PARAMETERS
	1.1: Starting conditions
	Set the parameters for the game to run after starting and before ending

	1.2: Win/loss conditions
		1.2.1: Win if enemy lives = 0
		1.2.2: Lose of player lives = 0

	1.3: Objects
		1.3.1: Instantiate the player
		1.3.2: Instantiate enemies
		1.3.3: Instantiate the base
			*/

			// default destructor function
	~Initialise();
};

