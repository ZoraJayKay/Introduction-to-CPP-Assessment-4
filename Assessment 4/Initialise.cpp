#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Initialise.h"

// Default member function constructor
Initialise::Initialise() {};

// Overloaded member function constructor with screen height and width
Initialise::Initialise(int windowWidth, int windowHeight)
{
	std::cout << "---Initialise constructor---" << endl;

	// Texture file paths included within this program's files
	playerShipFileName = "x64/Images/playerShip1_green.png";
	enemyShipFileName = "x64/Images/enemyBlack1.png";
	baseFileName = "x64/Images/spaceBuilding_009.png";
	backgroundFileName = "x64/Images/black.png";

	//1: GAME PARAMETERS
		//1.1: Starting conditions / parameters for the game to run after starting and before ending
		// Choose how many enemies there will be
		numberOfBases = 5;
		numberOfEnemies = 5;
		
		// 1.2: Win/loss conditions
		// 1.2.1: Win if enemy lives = 0
		// 1.2.2: Lose of player lives = 0

		// 1.3: Objects
		// 1.3.1	*** |||	PLAYER ||| ***
		//			***		PLAYER OBJECT & SPRITE	***
		CreatePlayer(windowWidth, windowHeight);

		// 1.3.2	*** |||	ENEMIES ||| ***
		//		***		ENEMY OBJECT	***
		CreateEnemy(numberOfEnemies, windowWidth, windowHeight);

		// 1.3.3	*** |||	BASES ||| ***
		//		***		BASE OBJECT	***
		CreateBase(numberOfBases, windowWidth, windowHeight);				
}

// member function for destructor
Initialise::~Initialise() {
	delete playerObjectPtr;
	playerObjectPtr = nullptr;

	delete playerSpritePtr;
	playerSpritePtr = nullptr;
}

//	***	---	INSTANTIATION FUNCTIONS	---	***
	// Implement these eventually rather than doing it manually 
		// A function to create a new player
		void Initialise::CreatePlayer(int width, int height) {
			//	1.3.1.1: Set the pointer of the player to its instantiated object
			playerObjectPtr = new Player(1, true, 0, playerObjectPtr->Laser);
			// Lives = 1.
				// Has weapon = true.
				// Score = 0.
				// Weapon = laser

			//	1.3.1.2: Set the pointer of the player to its instantiated object and load the sprite a texture
			playerSpritePtr = new SpriteObject(playerShipFileName, playerSpritePtr->Friendly_Sprite_Type);
			//	1.3.1.3: Set the pointer of the player's collider
			//playerCollider = new AABB(/* min and max */);

			//	1.3.1.4: Make the 'position' of the sprite object at its centre to give it a central point of rotation
			playerSpritePtr->SetPosition(-playerSpritePtr->Width() / 2.0f, playerSpritePtr->Height() / 2.0f);
			//	1.3.1.5: Make the player sprite the child of the player object
			playerObjectPtr->AddChild(*playerSpritePtr);
			//	1.3.1.6: Set the initial position for the playerObject (and thus child as well)
			playerObjectPtr->SetPosition(width / 2, height * 0.8f);
			//	1.3.1.7: Only initialise the AABB of the sprite 
			AABBsToInitialise.push_back(playerSpritePtr->colliderPtr);
		};

		// A function to create a new enemy
		void Initialise::CreateEnemy(int number, int width, int height) {
			for (int i = 0; i < number; i++) {
				//	1.3.2.1: Set pointers of the enemy and its sprite to their objects
				Enemy* enemyPtr = new Enemy(250, enemyPtr->Laser);
				//enemyPtr = new Enemy(250, enemyPtr->Laser);
					// Move speed = 250.
					// Weapon = laser
				//	1.3.2.2: Load the sprite a texture
				SpriteObject* enemySpritePtr = new SpriteObject(enemyShipFileName, enemySpritePtr->Enemy_Sprite_Type);
				//	1.3.2.3: Make the 'position' of the sprite object at its centre to give it a central point of rotation
				enemySpritePtr->SetPosition(-enemySpritePtr->Width() / 2.0f, enemySpritePtr->Height() / 2.0f);
				//	1.3.2.4: Make the sprite the child of the parent object
				enemyPtr->AddChild(*enemySpritePtr);
				//	1.3.2.5: Set the initial position for the object (and thus child as well)
				// Proportionately distribute the bases over the screen, with an offset to account for the fact  that their (0,0) XY is the top left of their shape
				enemyPtr->SetPosition(
					(width / (numberOfEnemies + 1)) * (i + 1) - (enemySpritePtr->Width()),
					height * 0.05f);
				//	1.3.2.6: Add the new enemy to the list of enemies to initialise
				enemiesToInitialise.push_back(enemyPtr);
				AABBsToInitialise.push_back(enemySpritePtr->colliderPtr);
			}
		};

		// A function to create a new base
		void Initialise::CreateBase(int number, int width, int height) {
			for (int i = 0; i < numberOfBases; i++) {
				//	1.3.3.1: Set pointers of the bases to their new objects
				Base* base = new Base(width, height);

				//	1.3.3.2: Set the initial position for the object (and thus children as well)
				base->SetPosition(
					// Proportionately distribute the bases over the screen, with an offset to account for the fact  that their (0,0) XY is the top left of their shape
					((width / (numberOfBases + 1)) * (i + 1)) - ((base->tileWidth * base->COLS * 0.5)),
					height * 0.6f);

				//	1.3.3.6: Add the new bases to the list of bases to initialise
				basesToInitialise.push_back(base);
			}
		};