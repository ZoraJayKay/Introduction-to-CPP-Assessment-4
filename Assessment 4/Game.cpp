#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Game.h"
#include "Initialise.h"
#include "Timer.h"
#include "Controller.h"
#include <string>

//// Program screen size
//int screenWidth = 1080;
//int screenHeight = 720;
//
//// Play area variables
//int playWidth = 1000;
//int playHeight = 660;

// Timer variables
float targetFps = 60.0f;
float elapsedTime = 0.0f;
int frames = 0;

// 1: Initialise a game session (default constructor)
Game::Game() 
{
	std::cout << "---Game constructor---" << endl;
	
	// Program screen size
	screenWidth = 1080;
	screenHeight = 720;

	// Play area variables
	playWidth = 1000;
	playHeight = 660;

	// Print message in program banner at top of screen
	// NOTE TO SELF: InitWindow needs to be done BEFORE loading any textures
	InitWindow(screenWidth, screenHeight, "Zora Jane Kerr: Introduction to C++ (Assessment 4 - Retro Game) Space Invaders (AIE, 2023 [student year 1])");

	// 1.1: Initialise a game session
	// Initialise a pointer to a new instance of the Initialise class.
	// The Initialise class instance (init) will in turn set all of the parameters that constitute the starting conditions of the game.	
	init = new Initialise();

	// 1.2: Add the objects from initialisation to the scene as root objects
	AddRootObject(*(init->playerObjectPtr));
	AddRootObject(*(init->enemyPtr));
	// AddRootObject(*(init(base objects));

	// 1.3: Initialise a pointer to a new instance of the Controller class.
	cntrlr = new Controller();

	// 1.4 Permit the controller to make use of a game class pointer
	cntrlr->g = this;

	SetTargetFPS(60);
}

Game::~Game() 
{
	// Delete the pointer for the initialisation process
	delete init;
	init = nullptr;

	for (GameObject* obj : rootObjectsToAdd) {
		delete obj;
		obj = nullptr;
	}

	for (GameObject* obj : rootObjectsToRemove) {
		delete obj;
		obj = nullptr;
	}

	// Delete all of the vectors of game object pointers for the game actors
	for (GameObject* obj : rootObjects) {
		delete obj;
		obj = nullptr;
	}

	// Delete the controller pointer
	delete cntrlr;
	cntrlr = nullptr;
}



// 2: UPDATE FUNCTION
void Game::Update()
{
	// 2.1: Update the game timer
		// 2.1.1: Instantiate a timer if one doesn't already exist
		gameTimer = Timer::Instance();
		// 2.1.2: Update delta time
		gameTimer->Tick();
		// 2.1.3: Reset the clock's 'start' timer
		gameTimer->Reset();
		// 2.1.4: Increment the timer with delta time
		elapsedTime += gameTimer->DeltaTime();

			// Increment the frames (may or may not be using a frame counter)
			frames++;

	// 2.2: Update the game
		if (elapsedTime >= gameTimer->DeltaTime()) {
			// vvv		these are just a few time-based metrics that may or may not be in use printing to the console	vvv
			// print framerate
			// std::cout << frames / elapsedTime << endl;	

			// 2.2.1: Update the object hierarchy including adding and removing parent / child relationships
			UpdateRelationships();

			// 2.2.2: Update the arithmetic underlying movement and drawing
			UpdateCalculations();

			// 2.2.3: Debug if necessary
			//Debug();

			// 2.2.4: Draw the game scene
			Draw();			
		}
}


// 2.2.1: Update the object hierarchy including adding and removing parent / child relationships
void Game::UpdateRelationships()
{
	//***	ADDING ROOT OBJECTS		***
		// for each pointer in the vector of objects to remove...
		for (GameObject* obj : rootObjectsToAdd) {
			// add the pointer to the object to the back of the vector of root objects
			rootObjects.push_back(obj);
		}
	
		// clear the add-pending objects vector
		rootObjectsToAdd.clear();


	//***	REMOVING ROOT OBJECTS		***
		// For any objects destroyed...
		// 
		
		// For any objects that have left the play area...
		for (GameObject* obj : rootObjects) {
			if (
				// if x axis is off the width, or...
				(obj->GlobalTransform().m02 < 0 || obj->GlobalTransform().m02 > screenWidth) ||
				// if y axis is off the height...
				(obj->GlobalTransform().m12 < 0 || obj->GlobalTransform().m12 > screenHeight))
			{
				RemoveRootObject(*obj);
			}
		};
		
		// for each pointer in the vector of objects to remove...
		for (GameObject* obj : rootObjectsToRemove) {
		
			// create an iterator which will find the pointer to remove in the rootObjects vector
			vector<GameObject*>::iterator itr = find(rootObjects.begin(), rootObjects.end(), obj);
		
			// save the position between index 0 and the found pointer
			int index = distance(rootObjects.begin(), itr);

			// erase the found pointer from the vector
			rootObjects.erase(rootObjects.begin() + index);
		}

		// clear the remove-pending objects vector
		rootObjectsToRemove.clear();
}

// 1.2.1: Add objects created since last update to the list of root objects
void Game::AddRootObject(GameObject& obj) {
	// Create a pointer of the object reference passed in 
	GameObject* objPtr = &obj;
	// Add the new pointer to the object passed in to the vector
	rootObjectsToAdd.push_back(objPtr);
};

// 1.2.2: Add objects targeted for removal since last update to a list
void Game::RemoveRootObject(GameObject& obj) {
	// Create a pointer of the object reference passed in 
	GameObject* objPtr = &obj;
	// Add the new pointer to the object passed in to the vector
	rootObjectsToRemove.push_back(objPtr);
};

// 2.2.2: Update the arithmetic underlying movement and drawing
void Game::UpdateCalculations() 
{
	// Update the calculations for all root objects (and thus their children)
	for (GameObject* obj : rootObjects) {
		// Call the Update function that is defined in the GameObject class
		obj->Update(gameTimer->DeltaTime(), *cntrlr);
	}
}

// 2.2.4: Draw the game scene
void Game::Draw() 
{
	BeginDrawing();

	// 2.2.4.1: Create the visible play area
	ClearBackground(RAYWHITE);

	// 2.2.4.2: Write information to the screen
	// Score
	PrintPlayerScore();
	// Lives
	PrintPlayerLives();

	// 2.2.4.3: Draw all root objects (and thus their children)
	for (GameObject* obj : rootObjects) {
		// Call the Draw function that is defined in the GameObject class
		obj->Draw();
	}

	EndDrawing();
}

void Game::PrintPlayerScore() {
	//int playerScore = init->playerObjectPtr->score;
	string playerScoreString = to_string(init->playerObjectPtr->score);
	string scoreString = "Score:	" + playerScoreString;
	const char* score = scoreString.c_str();
	DrawText(score, 20, 40, 20, RED);
};

void Game::PrintPlayerLives() {
	//int playerScore = init->playerObjectPtr->score;
	string playerLivesString = to_string(init->playerObjectPtr->lives);
	string livesString = "Lives:	" + playerLivesString;
	const char* lives = livesString.c_str();
	DrawText(lives, 20, 70, 20, RED);
};


void Game::Debug() {
	// Create a string out of the player score
	//std::string s = to_string(init->playerObjectPtr->score);
	// Create a const char pointer that points to the address of the string 's' as an array of characters
	//const char* scr = s.c_str();

	int playerCount = 0;
	int enemyCount = 0;
	int baseCount = 0;
	int enemyAttackCount = 0;
	int friendlyAttackCount = 0;

	// Player object global x location
	float playerX = init->playerObjectPtr->GlobalTransform().m02;
	std::string plyrX = to_string(playerX);
	const char* x = plyrX.c_str();

	// Player sprite global x location
	float spriteX = init->playerSpritePtr->GlobalTransform().m02;
	std::string sprtX = to_string(playerX);
	const char* sX = sprtX.c_str();

	DrawText(x, 50, 40, 20, LIGHTGRAY);
	DrawText(sX, 50, 80, 20, LIGHTGRAY);


	// CONSOLE DEBUG: COUNT THE PLAYER OBJECTS
	for (GameObject* obj : rootObjects) {
		if (obj->objType == GameObject::Player_Type) {
			playerCount++;
		}
	}

	// CONSOLE DEBUG: COUNT THE ENEMY OBJECTS
	for (GameObject* obj : rootObjects) {
		if (obj->objType == GameObject::Enemy_Type) {
			enemyCount++;
		}
	}

	// CONSOLE DEBUG: COUNT THE BASE OBJECTS
	for (GameObject* obj : rootObjects) {
		if (obj->objType == GameObject::Base_Type) {
			baseCount++;
		}
	}

	// CONSOLE DEBUG: COUNT THE ENEMY PROJECTILE OBJECTS
	for (GameObject* obj : rootObjects) {
		if (obj->objType == GameObject::Enemy_Projectile_Type) {
			enemyAttackCount++;
		}
	}

	// CONSOLE DEBUG: COUNT THE FRIENDLY PROJECTILE OBJECTS
	for (GameObject* obj : rootObjects) {
		if (obj->objType == GameObject::Friendly_Projectile_Type) {
			friendlyAttackCount++;
		}
	}
	

	std::cout << "Number of Root objects: " << rootObjects.size() << std::endl;
	std::cout << "Number of Player objects: " << playerCount << std::endl;
	std::cout << "Number of Enemy objects: " << enemyCount << std::endl;
	std::cout << "Number of Base objects: " << baseCount << std::endl;
	std::cout << "Number of Weapon objects: " << enemyAttackCount << std::endl;
	std::cout << "Number of Weapon objects: " << friendlyAttackCount << std::endl;
	std::cout << "Player weapon equipped: " << init->playerObjectPtr->GetWeapon() << std::endl;
	DebugCheckWeapon();
}

void Game::DebugCheckWeapon() {
	switch (init->playerObjectPtr->GetWeapon()) {
	case 0:	// Laser fire
		// Load laser attack texture
		//spritePtr->Load(laserAttackFileName);
		// set spawn point to the end of the barrel of the weapon
		//spritePtr->SetPosition(spritePtr->Height() * 2.5f, -spritePtr->Width() / 2);
		std::cout << "Laser equipped" << std::endl;
		break;

	case 1:	// name of weapon
		std::cout << "Double laser equipped" << std::endl;
		break;

	case 2:	// name of weapon
		std::cout << "Weapon not equipped" << std::endl;
		break;

	case 3:	// name of weapon
		std::cout << "Weapon not equipped" << std::endl;
		break;
	}
};