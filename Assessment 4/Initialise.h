#pragma once

#include <iostream>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "SpriteObject.h"
#include "Base.h"
#include "AABB.h"

using namespace std;

// Set the parameters for the game to run after starting and before ending

class Initialise
{

private:


protected:
	

public: 
	/* 1: GAME PARAMETERS
		1.1: Starting conditions
		Set the parameters for the game to run after starting and before ending
			// Screen Width
			// Screen height

		1.2: Win/loss conditions
			1.2.1: Win if enemy lives = 0
			1.2.2: Lose of player lives = 0

		1.3: Objects
			1.3.1: Instantiate the player
			1.3.2: Instantiate enemies
			1.3.3: Instantiate the base
				*/

	// Public pointers that other classes can access
	// PLAYER
	class Player* playerObjectPtr;
	class SpriteObject* playerSpritePtr;

	// ENEMIES
	int numberOfEnemies;

	// Array row and column volumes for enemy waves
	/*static const int ROWS = 5;
	static const int COLS = 5;*/

	vector<Enemy*> enemiesToInitialise;

	// BASE
	int numberOfBases;
	vector<Base*> basesToInitialise;

	// AABBs
	vector<AABB*> AABBsToInitialise;

	// File path variables
	const char* playerShipFileName;
	const char* enemyShipFileName;
	const char* baseFileName;
	const char* backgroundFileName;

	Initialise();
	Initialise(int windowWidth, int windowHeight, int playerLives, int numEnemies, int numBases);

	// default destructor function
	~Initialise();

	//	***	---	INSTANTIATION FUNCTIONS	---	***
		// Implement eventually rather than doing it manually 
			// A function to create a new player
			void CreatePlayer(int lives, int width, int height);

			// A function to create a new enemy
			void CreateEnemy(int number, int width, int height);

			// A function to create a new base
			void CreateBase(int number, int width, int height);

};

