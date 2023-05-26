#pragma once

#include <iostream>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "SpriteObject.h"
#include "Base.h"

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
	class Enemy* enemyPtr;
	class SpriteObject* enemySpritePtr;
	vector<Enemy*> enemiesToInitialise;

	// BASE
	class Base* basePtr_01;
	class Base* basePtr_02;
	class Base* basePtr_03;
	class SpriteObject* baseSpritePtr_01;
	class SpriteObject* baseSpritePtr_02;
	class SpriteObject* baseSpritePtr_03;
	vector<Base*> basesToInitialise;

	// File path variables
	const char* playerShipFileName;
	const char* enemyShipFileName;
	const char* baseFileName;
	const char* backgroundFileName;

	Initialise();
	Initialise(int windowWidth, int windowHeight);

	// default destructor function
	~Initialise();


	//	***	---	INSTANTIATION FUNCTIONS	---	***
		// Implement eventually rather than doing it manually 
			// A function to create a new player
			void CreatePlayer();

			// A function to create a new enemy
			void CreateEnemy();

			// A function to create a new base
			void CreateBase();

};

