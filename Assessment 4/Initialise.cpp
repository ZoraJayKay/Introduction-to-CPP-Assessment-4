#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Initialise.h"

// Default member function constructor
Initialise::Initialise() {};

// Overloaded member function constructor with screen height and width
Initialise::Initialise(int screenWidth, int screenHeight)
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
			   //		***		PLAYER OBJECT	***
			   //	1.3.1.1: Set pointers of the player and its sprite to their objects
			   //playerObjectPtr = new Player(1, true, 0, (GameObject::weaponType)0);
	playerObjectPtr = new Player(1, true, 0, playerObjectPtr->Laser);
	playerSpritePtr = new SpriteObject();
	// Lives = 1.
	// Has weapon = true.
	// Score = 0.
	// Weapon = laser

//		***		PLAYER SPRITE	***
//	1.3.1.2: Load the sprite a texture
	playerSpritePtr->Load(playerShipFileName);
	//	1.3.1.3: Make the 'position' of the sprite object at its centre to give it a central point of rotation
	playerSpritePtr->SetPosition(-playerSpritePtr->Width() / 2.0f, playerSpritePtr->Height() / 2.0f);
	//	1.3.1.4: Make the player sprite the child of the player object
	playerObjectPtr->AddChild(*playerSpritePtr);
	//	1.3.1.5: Set the initial position for the playerObject (and thus child as well)
	playerObjectPtr->SetPosition(screenWidth / 2, screenHeight * 0.8f);

	// vvv		NOT YET IMPLEMENTED		vvv
	//	1.3.1.1: Set initial position
	//	1.3.1.2: Offset the player object to the middle of its object rather than top left
	//	1.3.1.3: set size of the offset for collision detection?


// 1.3.2	*** |||	ENEMIES ||| ***
	//		***		ENEMY OBJECT	***
	//	1.3.2.1: Set pointers of the enemy and its sprite to their objects
	enemyPtr = new Enemy(250, enemyPtr->Laser);
	enemySpritePtr = new SpriteObject;
	// Move speed = 250.
	// Weapon = laser

//		***		ENEMY SPRITE	***
//	1.3.2.2: Load the sprite a texture
	enemySpritePtr->Load(enemyShipFileName);
	//	1.3.2.3: Make the 'position' of the sprite object at its centre to give it a central point of rotation
	enemySpritePtr->SetPosition(-enemySpritePtr->Width() / 2.0f, enemySpritePtr->Height() / 2.0f);
	//	1.3.2.4: Make the sprite the child of the parent object
	enemyPtr->AddChild(*enemySpritePtr);
	//	1.3.2.5: Set the initial position for the object (and thus child as well)
	enemyPtr->SetPosition(screenWidth / 2.0f, screenHeight * 0.05f);
	//	1.3.2.6: Add the new enemy to the list of enemies to initialise
	//enemiesToInitialise.push_back(enemyPtr);

	// 1.3.3	*** |||	BASES ||| ***
	//		***		BASE OBJECT	***
	//	1.3.3.1: Set pointers of the bases and their sprites to their objects
	basePtr_01 = new Base(screenWidth, screenHeight);
	basePtr_02 = new Base(screenWidth, screenHeight);
	basePtr_03 = new Base(screenWidth, screenHeight);
	/*baseSpritePtr_01 = new SpriteObject;
	baseSpritePtr_02 = new SpriteObject;
	baseSpritePtr_03 = new SpriteObject;*/

	//		***		BASE SPRITES	***
	//	1.3.3.2: Load the sprite a texture
	/*baseSpritePtr_01->Load(baseFileName);
	baseSpritePtr_02->Load(baseFileName);
	baseSpritePtr_03->Load(baseFileName);*/

	//	1.3.3.3: Make the 'position' of the sprite object at its centre to give it a central point of rotation
	/*baseSpritePtr_01->SetPosition(-baseSpritePtr_01->Width() / 2.0f, baseSpritePtr_01->Height() / 2.0f);
	baseSpritePtr_02->SetPosition(-baseSpritePtr_02->Width() / 2.0f, baseSpritePtr_02->Height() / 2.0f);
	baseSpritePtr_03->SetPosition(-baseSpritePtr_03->Width() / 2.0f, baseSpritePtr_03->Height() / 2.0f);*/

	//	1.3.3.5: Set the initial position for the object (and thus child as well)
	basePtr_01->SetPosition((screenWidth / 4.0f) * 1, screenHeight * 0.75f);
	basePtr_02->SetPosition((screenWidth / 4.0f) * 2, screenHeight * 0.75f);
	basePtr_03->SetPosition((screenWidth / 4.0f) * 3, screenHeight * 0.75f);

	//	1.3.3.4: Make the sprite the child of the parent object
	/*baseSpritePtr_01->AddChild(*basePtr_01);
	baseSpritePtr_02->AddChild(*basePtr_02);
	baseSpritePtr_03->AddChild(*basePtr_03);*/

	//	1.3.3.6: Add the new bases to the list of bases to initialise
	/*basesToInitialise.push_back(basePtr_01);
	basesToInitialise.push_back(basePtr_02);
	basesToInitialise.push_back(basePtr_03);*/


		/* 1.3.2.1: Set initial position
		*
		//	1.3.3:	Rotate the sprite to be facing forward
		//playerSprite->SetRotate(-90 * (float)(PI / 180.0f));

			1.3.2.2: Offset the enemy object to the middle of its object rather than top left
			1.3.2.3: set size of the offset for collision detection?

		1.3.3: Instantiate the base
			1.3.3.1: Set position
			1.3.3.2: Set lives = 1
			1.3.3.3: Set position
			1.3.3.4: Instantiate sprites

*/
}

// member function for destructor
Initialise::~Initialise() {
	delete playerObjectPtr;
	playerObjectPtr = nullptr;

	delete playerSpritePtr;
	playerSpritePtr = nullptr;
}

//	***	---	INSTANTIATION FUNCTIONS	---	***
	// Implement eventually rather than doing it manually 
		// A function to create a new player
		void Initialise::CreatePlayer() {};

		// A function to create a new enemy
		void Initialise::CreateEnemy() {};

		// A function to create a new base
		void Initialise::CreateBase() {};