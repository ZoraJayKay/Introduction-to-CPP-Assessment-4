#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Initialise.h"
#include "Player.h"
#include "Enemy.h"
#include "SpriteObject.h"

// member function constructor
Initialise::Initialise() 
{
	std::cout << "---Initialise constructor---" << endl;

	// texture file paths
	playerShipFileName = "x64/Images/playerShip1_green.png";
	enemyShipFileName = "";
	baseFileName = "";

	 //1: GAME PARAMETERS
		//1.1: Starting conditions
		//Set the parameters for the game to run after starting and before ending

		//1.2: Win/loss conditions
		//	1.2.1: Win if enemy lives = 0
		//	1.2.2: Lose of player lives = 0

	//1.3: Objects
	//	1.3.1: Instantiate pointers to the player and its sprite
	//Player* playerObject = new Player(1, true, 0);
	
	playerObject = new Player(1, true, 0);
	SpriteObject* playerSprite = new SpriteObject();
		// Lives = 1.
		// Has weapon = true.
		// Score = 0.

	//		***		PLAYER SPRITE	***
	//	1.3.2: Load the sprite a texture
	playerSprite->Load(playerShipFileName);
	//	1.3.4: Make the point of rotation for the sprite at its centre
	playerSprite->SetPosition(-playerSprite->Width() / 2.0f, playerSprite->Height() / 2.0f);

	//		***		PLAYER OBJECT	***
	

	// 1.3.1.1: Set initial position
	// 1.3.1.2: Offset the player object to the middle of its object rather than top left
	// 1.3.1.3: set size of the offset for collision detection?			
	
	// Parent the player sprite to the player object
	playerObject->AddChild(*playerSprite);
		
	//	1.3.5: Set the initial position for the playerObject
	playerObject->SetPosition(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);


			 /*1.3.2: Instantiate enemies and their sprites*/
	Enemy* enemy = new Enemy;
	SpriteObject* enemySprite = new SpriteObject;
			
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
Initialise::~Initialise() 
{

}