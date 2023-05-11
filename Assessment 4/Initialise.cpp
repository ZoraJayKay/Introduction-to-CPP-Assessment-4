#include "Initialise.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "Player.h"
#include "Enemy.h"
#include "SpriteObject.h"

// member function constructor
Initialise::Initialise() 
{
	std::cout << "---Initialise constructor---" << endl;

	 //1: GAME PARAMETERS
		//1.1: Starting conditions
		//Set the parameters for the game to run after starting and before ending
		//	1.1.1: Create the visible play area
		//	MOVED TO PROGRAM CLASS FOR SIMPLICITY

		//	1.1.2: Create a timer
		//	1.1.3: Create and set player score = 0
		//	1.1.4 Set target FPS

		//1.2: Win/loss conditions
		//	1.2.1: Win if enemy lives = 0
		//	1.2.2: Lose of player lives = 0

		//1.3: Objects
		//	1.3.1: Instantiate pointers to the player and its sprite
	Player* playerObject = new Player(1, true, 0);
	SpriteObject* playerSprite = new SpriteObject();
		// Lives = 1.
		// Has weapon = true.
		// Score = 0.

		//	1.3.2: Load the sprite a texture
	playerSprite->Load("");	// POPULATE WITH FILE PATH

		//	1.3.3: Set the initial position for the playerObject
	playerObject->SetPosition(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);

		//	1.3.4: Make the point of rotation for the playerObject at its centre
	// fill

		//	1.3.5:	Rotate the sprite to be facing forward
	playerSprite->SetRotate(-90 * (float)(PI / 180.0f));

		//	1.3.5: Make the point of rotation for the sprite at its centre
	playerSprite->SetPosition(-playerSprite->Width() / 2.0f, playerSprite->Height() / 2.0f);


			/*1.3.1.1: Set initial position
			1.3.1.2: Offset the player object to the middle of its object rather than top left
			1.3.1.3: set size of the offset for collision detection?			
		

			 /*1.3.2: Instantiate enemies and their sprites*/
	Enemy* enemy = new Enemy;
	SpriteObject* enemySprite = new SpriteObject;
			
			/* 1.3.2.1: Set initial position
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
Initialise::~Initialise() 
{

}