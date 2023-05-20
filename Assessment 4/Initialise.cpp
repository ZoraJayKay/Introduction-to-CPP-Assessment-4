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
				playerObjectPtr = new Player(1, true, 0, (GameObject::weaponType)0);
				playerSpritePtr = new SpriteObject();
					// Lives = 1.
					// Has weapon = true.
					// Score = 0.

				//		***		PLAYER SPRITE	***
				//	1.3.1.2: Load the sprite a texture
				playerSpritePtr->Load(playerShipFileName);
				//	1.3.1.3: Make the 'position' of the sprite object at its centre to give it a central point of rotation
				playerSpritePtr->SetPosition(-playerSpritePtr->Width() / 2.0f, playerSpritePtr->Height() / 2.0f);
				//	1.3.1.4: Make the player sprite the child of the player object
				playerObjectPtr->AddChild(*playerSpritePtr);
				//	1.3.1.5: Set the initial position for the playerObject (and thus child as well)
				playerObjectPtr->SetPosition(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);

				// vvv		NOT YET IMPLEMENTED		vvv
				//	1.3.1.1: Set initial position
				//	1.3.1.2: Offset the player object to the middle of its object rather than top left
				//	1.3.1.3: set size of the offset for collision detection?


			// 1.3.2	*** |||	ENEMY ||| ***
				//		***		ENEMY OBJECT	***
				//	1.3.2.1: Set pointers of the enemy and its sprite to their objects
				enemyPtr = new Enemy;
				enemySpritePtr = new SpriteObject;
			
				//		***		ENEMY SPRITE	***
				//	1.3.2.2: Load the sprite a texture
				enemySpritePtr->Load(enemyShipFileName);
				//	1.3.2.3: Make the 'position' of the sprite object at its centre to give it a central point of rotation
				enemySpritePtr->SetPosition(-enemySpritePtr->Width() / 2.0f, enemySpritePtr->Height() / 2.0f);
				//	1.3.2.4: Make the player sprite the child of the player object
				enemyPtr->AddChild(*enemySpritePtr);
				//	1.3.2.5: Set the initial position for the playerObject (and thus child as well)
				enemyPtr->SetPosition(GetScreenWidth() / 2.0f, GetScreenHeight() / 5.0f);


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