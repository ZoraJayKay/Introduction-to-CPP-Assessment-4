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

	   //1.2: Win/loss conditions
		   //	1.2.1: Win if enemy lives = 0
		   //	1.2.2: Lose of player lives = 0

	   //1.3: Objects
		   //	1.3.1	*** |||	PLAYER ||| ***
		   //			***		PLAYER OBJECT & SPRITE	***
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
				playerObjectPtr->SetPosition(windowWidth / 2, windowHeight * 0.8f);
				//	1.3.1.7: Only initialise the AABB of the sprite 
				AABBsToInitialise.push_back(playerSpritePtr->colliderPtr);

			// 1.3.2	*** |||	ENEMIES ||| ***
				//		***		ENEMY OBJECT	***
				//	1.3.2.1: Set pointers of the enemy and its sprite to their objects
				enemyPtr = new Enemy(250, enemyPtr->Laser);
					// Move speed = 250.
					// Weapon = laser
				//	1.3.2.2: Load the sprite a texture
				enemySpritePtr = new SpriteObject(enemyShipFileName, enemySpritePtr->Enemy_Sprite_Type);
				//	1.3.2.3: Set the pointer of the enemy's collider
				//enemyCollider = new AABB(/* min and max */);

				//	1.3.2.4: Make the 'position' of the sprite object at its centre to give it a central point of rotation
				enemySpritePtr->SetPosition(-enemySpritePtr->Width() / 2.0f, enemySpritePtr->Height() / 2.0f);
				//	1.3.2.5: Make the sprite the child of the parent object
				enemyPtr->AddChild(*enemySpritePtr);
				//	1.3.2.6: Set the initial position for the object (and thus child as well)
				enemyPtr->SetPosition(windowWidth / 2.0f, windowHeight * 0.05f);
				//	1.3.2.6: Add the new enemy to the list of enemies to initialise
				enemiesToInitialise.push_back(enemyPtr);
				AABBsToInitialise.push_back(enemySpritePtr->colliderPtr);

			// 1.3.3	*** |||	BASES ||| ***
				//		***		BASE OBJECT	***
				//	1.3.3.1: Set pointers of the bases and their sprites to their objects
				basePtr_01 = new Base(windowWidth, windowHeight);
				basePtr_02 = new Base(windowWidth, windowHeight);
				basePtr_03 = new Base(windowWidth, windowHeight);
				/*//	1.3.3.2: Load the sprite a texture
				baseSpritePtr_01 = new SpriteObject(baseFileName);
				baseSpritePtr_02 = new SpriteObject(baseFileName);
				baseSpritePtr_03 = new SpriteObject(baseFileName);*/

				//	1.3.3.3: Make the 'position' of the sprite object at its centre to give it a central point of rotation
				/*baseSpritePtr_01->SetPosition(-baseSpritePtr_01->Width() / 2.0f, baseSpritePtr_01->Height() / 2.0f);
				baseSpritePtr_02->SetPosition(-baseSpritePtr_02->Width() / 2.0f, baseSpritePtr_02->Height() / 2.0f);
				baseSpritePtr_03->SetPosition(-baseSpritePtr_03->Width() / 2.0f, baseSpritePtr_03->Height() / 2.0f);*/

				//	1.3.3.5: Set the initial position for the object (and thus child as well)
				basePtr_01->SetPosition((windowWidth / 4.0f) * 1, windowHeight * 0.7f);
				basePtr_02->SetPosition((windowWidth / 4.0f) * 2, windowHeight * 0.7f);
				basePtr_03->SetPosition((windowWidth / 4.0f) * 3, windowHeight * 0.7f);

				//	1.3.3.4: Make the sprite the child of the parent object
				/*baseSpritePtr_01->AddChild(*basePtr_01);
				baseSpritePtr_02->AddChild(*basePtr_02);
				baseSpritePtr_03->AddChild(*basePtr_03);*/

				//	1.3.3.6: Add the new bases to the list of bases to initialise
				basesToInitialise.push_back(basePtr_01);
				basesToInitialise.push_back(basePtr_02);
				basesToInitialise.push_back(basePtr_03);
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
		void Initialise::CreatePlayer() {};

		// A function to create a new enemy
		void Initialise::CreateEnemy() {};

		// A function to create a new base
		void Initialise::CreateBase() {};