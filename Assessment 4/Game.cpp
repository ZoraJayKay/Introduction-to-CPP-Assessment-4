#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Game.h"
#include "Initialise.h"
#include "Timer.h"
#include "Controller.h"
#include <string>

// Timer variables
float targetFps = 60.0f;
float elapsedTime = 0.0f;
int frames = 0;

// 0: Initialise a game session (default constructor)
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

	// 0.1: Initialise a game session
		// Initialise a pointer to a new instance of the Initialise class.
		// The Initialise class instance (init) will in turn set all of the parameters that constitute the starting conditions of the game.	
		init = new Initialise(screenWidth, screenHeight);
		// Add number of enemies
		// Add number of bases
		// Add difficulty that sets the above etc?

	// 0.2: Add the objects from initialisation to the scene as root, enemy and base objects
		// 0.2.1: Add the player
		AddRootObject(*(init->playerObjectPtr));
		//AddRootObject(*(init->enemyPtr));
		//AddRootObject(*(init->basePtr_01));
		//AddRootObject(*(init->basePtr_02));
		//AddRootObject(*(init->basePtr_03));


		// 0.2.2: Add the vector of enemies from initialisation
			// This adds the enemies WAITING to be put on the master vector of enemies because at this point in time, initialise has run but Update() *has not* and so they have not been moved out of the pending list yet
			for (Enemy* enemy : init->enemiesToInitialise) {
					AddRootObject(*enemy);
					AddEnemyObject(*enemy);
				}

		// 0.2.3: Add the vector of bases from initialisation
			// This adds the bases WAITING to be put on the master vector of bases because at this point in time, initialise has run but Update() *has not* and so they have not been moved out of the pending list yet
			for (Base* base : init->basesToInitialise) {
					AddRootObject(*base);
					AddBaseObject(*base);
				}


	// 0.3: Initialise a pointer to a new instance of the Controller class.
	cntrlr = new Controller();

	// 0.4 Permit the controller to make use of a game class pointer so that the controller can access the object hierarchy for instantiating weapon attacks
	cntrlr->g = this;

	SetTargetFPS(60);
}


// 1: UPDATE FUNCTION
void Game::Update()
{
	// 1.1: Update the game timer
		// 1.1.1: Instantiate a timer if one doesn't already exist
		gameTimer = Timer::Instance();
		// 1.1.2: Update delta time
		gameTimer->Tick();
		// 1.1.3: Reset the clock's 'start' timer
		gameTimer->Reset();
		// 1.1.4: Increment the timer with delta time
		elapsedTime += gameTimer->DeltaTime();
			// Increment the frames (may or may not be using a frame counter)
			frames++;

	// 1.2: Update the game
		if (elapsedTime >= gameTimer->DeltaTime()) {
			// vvv		these are just a few time-based metrics that may or may not be in use printing to the console	vvv
			// print framerate
			// std::cout << frames / elapsedTime << endl;	

			// 1.2.1: Update the object hierarchy including adding and removing parent / child relationships
			UpdateRelationships();
			// 1.2.2: Update the arithmetic underlying movement and drawing
			UpdateCalculations();
			// 1.2.3: Debug if necessary
			Debug();
			// 1.2.4: Draw the game scene
			Draw();			
		}
}


// 1.2.1: Update the object hierarchy including adding and removing parent / child relationships
void Game::UpdateRelationships()
{
	//***	ADDING ROOT OBJECTS		***
		// for each pointer in the vector of objects to add...
		for (GameObject* obj : rootObjectsToAdd) {
			// add the pointer to the object to the back of the vector of root objects
			rootObjects.push_back(obj);
		}
	
		// clear the add-pending objects vector
		rootObjectsToAdd.clear();

	//***	ADDING ENEMY OBJECTS		***
		// for each pointer in the vector of enemies to add...
		for (Enemy* enemy : enemiesToAdd) {
			// add the pointer to the object to the back of the vector of enemy objects
			enemies.push_back(enemy);
		}

		// clear the add-pending objects vector
		enemiesToAdd.clear();

	//***	ADDING BASE OBJECTS		***
		// for each pointer in the vector of bases to add...
		for (Base* base : basesToAdd) {
			// add the pointer to the object to the back of the vector of enemy objects
			bases.push_back(base);
		}

		// clear the add-pending objects vector
		basesToAdd.clear();


	//***	REMOVING ENEMY OBJECTS		***		
		// BEFORE deleting the root object, remove enemies from the list of enemies
		// for each pointer in the vector of enemies to remove...
		for (Enemy* enemy : enemiesToRemove) {
			// create an iterator which will find the pointer to remove in the enemies vector
			vector<Enemy*>::iterator itr_01 = find(enemies.begin(), enemies.end(), enemy);

			// save the position between index 0 and the found pointer
			int index = distance(enemies.begin(), itr_01);

			// erase the found pointer from the vector
			enemies.erase(enemies.begin() + index);
		}

		// clear the remove-pending objects vector
		enemiesToRemove.clear();

	//***	REMOVING BASE OBJECTS		***		
		// BEFORE deleting the root object, remove enemies from the list of enemies
		// for each pointer in the vector of enemies to remove...
		for (Base* base : basesToRemove) {
			// create an iterator which will find the pointer to remove in the enemies vector
			vector<Base*>::iterator itr_01 = find(bases.begin(), bases.end(), base);

			// save the position between index 0 and the found pointer
			int index = distance(bases.begin(), itr_01);

			// erase the found pointer from the vector
			bases.erase(bases.begin() + index);
		}

		// clear the remove-pending objects vector
		basesToRemove.clear();


	//***	REMOVING ROOT OBJECTS		***		
		// A: Add any objects destroyed by projectiles to the list to delete
		// FILL

		// B: Add any objects that have left the play area to the list to delete
		// for each pointer in the vector of objects to remove...
		for (GameObject* obj : rootObjects) {
			if (
				// if x axis is off the width, or...
				(obj->GlobalTransform().m02 < 0 || obj->GlobalTransform().m02 > screenWidth) ||
				// if y axis is off the height...
				(obj->GlobalTransform().m12 < 0 || obj->GlobalTransform().m12 > screenHeight))
			{
				// Add the object to the list of objects to remove
				RemoveRootObject(*obj);
			}
		};

		// C: Delete A + B
		// for each pointer in the vector of objects to remove...
		for (GameObject* obj : rootObjectsToRemove) {
			// create an iterator which will find the pointer to remove in the rootObjects vector
			vector<GameObject*>::iterator itr_02 = find(rootObjects.begin(), rootObjects.end(), obj);
		
			// save the position between index 0 and the found pointer
			int index = distance(rootObjects.begin(), itr_02);

			// erase the found pointer from the vector
			rootObjects.erase(rootObjects.begin() + index);
		}

		// clear the remove-pending objects vector
		rootObjectsToRemove.clear();
}

// Functions to facilitate the update of relationships
// 1.2.1.1: Add objects created since last update to the list of root objects
void Game::AddRootObject(GameObject& obj) {
	// Create a pointer of the object reference passed in 
	GameObject* objPtr = &obj;
	// Add the new pointer to the object passed in to the vector
	rootObjectsToAdd.push_back(objPtr);
};

// 1.2.1.2: Add objects targeted for removal since last update to a list
void Game::RemoveRootObject(GameObject& obj) {
	// Create a pointer of the object reference passed in 
	GameObject* objPtr = &obj;
	// Add the new pointer to the object passed in to the vector
	rootObjectsToRemove.push_back(objPtr);
};

// 1.2.1.3: Add enemy objects created since last update to the list of enemy objects
void Game::AddEnemyObject(Enemy& enemy) {
	// Create a pointer of the object reference passed in 
	Enemy* enmyPtr = &enemy;
	// Add the new pointer to the object passed in to the vector
	enemiesToAdd.push_back(enmyPtr);
};

// 1.2.1.4: Add enemy objects targeted for removal since last update to a list
void Game::RemoveEnemyObject(Enemy& enemy) {
	// Create a pointer of the object reference passed in 
	Enemy* enmyPtr = &enemy;
	// Add the new pointer to the object passed in to the vector
	enemiesToRemove.push_back(enmyPtr);
};

// 1.2.1.4: Add base objects created since last update to the list of base objects
void Game::AddBaseObject(Base& base) {
	// Create a pointer of the object reference passed in 
	Base* basePtr = &base;
	// Add the new pointer to the object passed in to the vector
	basesToAdd.push_back(basePtr);
};

// 1.2.1.5: Add base objects targeted for removal since last update to a list
void Game::RemoveBaseObject(Base& base) {
	// Create a pointer of the object reference passed in 
	Base* basePtr = &base;
	// Add the new pointer to the object passed in to the vector
	basesToRemove.push_back(basePtr);
};




// 1.2.2: Update the arithmetic underlying movement and drawing
void Game::UpdateCalculations() 
{
	// Update the calculations for all root objects (and thus their children)
	for (GameObject* obj : rootObjects) {
		// Call the Update function that is defined in the GameObject class
		obj->Update(gameTimer->DeltaTime(), *cntrlr);
	}
}

// 1.2.3: Draw the game scene
void Game::Draw() 
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// 1.2.3.1 Print the player score to the screen
	PrintPlayerScore();
	// 1.2.3.2 Print the player's lives to the screen
	PrintPlayerLives();

	// 1.2.3.3: Draw all root objects (and thus their children)
	for (GameObject* obj : rootObjects) {
		// Call the Draw function that is defined in the GameObject class
		obj->Draw();
	}

	EndDrawing();
}

void Game::PrintPlayerScore() {
	string playerScoreString = to_string(init->playerObjectPtr->score);
	string scoreString = "Score:	" + playerScoreString;
	const char* score = scoreString.c_str();
	DrawText(score, 20, 40, 20, RED);
};

void Game::PrintPlayerLives() {
	string playerLivesString = to_string(init->playerObjectPtr->lives);
	string livesString = "Lives:	" + playerLivesString;
	const char* lives = livesString.c_str();
	DrawText(lives, 20, 70, 20, RED);
};


Game::~Game()
{
	// Delete all of the vectors of enemy pointers
	for (Enemy* enemy : enemiesToAdd) {
		delete enemy;
		enemy = nullptr;
	}

	for (Enemy* enemy : enemiesToRemove) {
		delete enemy;
		enemy = nullptr;
	}

	for (Enemy* enemy : enemies) {
		delete enemy;
		enemy = nullptr;
	}

	// Delete all of the vectors of base pointers
	for (Base* base : basesToAdd) {
		delete base;
		base = nullptr;
	}

	for (Base* base : basesToRemove) {
		delete base;
		base = nullptr;
	}

	for (Base* base : bases) {
		delete base;
		base = nullptr;
	}

	// Delete all of the vectors of game object pointers for the game actors
	for (GameObject* obj : rootObjectsToAdd) {
		delete obj;
		obj = nullptr;
	}

	for (GameObject* obj : rootObjectsToRemove) {
		delete obj;
		obj = nullptr;
	}

	for (GameObject* obj : rootObjects) {
		delete obj;
		obj = nullptr;
	}

	// Delete the pointer for the initialisation process
	delete init;
	init = nullptr;

	// Delete the controller pointer
	delete cntrlr;
	cntrlr = nullptr;
}






void Game::Debug() {
	// Variables for tallying debug printouts
	int playerCount = 0;
	int enemyCount = 0;
	int baseCount = 0;
	int enemyAttackCount = 0;
	int friendlyAttackCount = 0;
	int enemyVectorCount = 0;
	int baseVectorCount = 0;

	// For statements to tall debug printouts
		// CONSOLE DEBUG: COUNT THE PLAYER OBJECTS
		for (GameObject* obj : rootObjects) {
			if (obj->objType == GameObject::Player_Type) {
				playerCount++;
			}
		}

		// CONSOLE DEBUG: COUNT THE ENEMY OBJECTS IN ROOT OBJECTS
		for (GameObject* obj : rootObjects) {
			if (obj->objType == GameObject::Enemy_Type) {
				enemyCount++;
			}
		}

		// CONSOLE DEBUG: COUNT THE ENEMY OBJECTS IN THEIR OWN VECTOR
		for (Enemy* enemy : enemies) {
			enemyVectorCount++;
		}

		// CONSOLE DEBUG: COUNT THE BASE OBJECTS IN ROOT OBJECTS
		for (GameObject* obj : rootObjects) {
			if (obj->objType == GameObject::Base_Type) {
				baseCount++;
			}
		}

		// CONSOLE DEBUG: COUNT THE BASE OBJECTS IN THEIR OWN VECTOR
		for (Base* base : bases) {
			baseVectorCount++;
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

	// DEBUG PRINTOUTS
		// Root object printouts
			// 
			
		// Player printouts
			// Debug print the player object global x location
			string playerXPositionString = to_string(init->playerObjectPtr->GlobalTransform().m02);
			string playerXString = "Player object x:	" + playerXPositionString;
			const char* playerX = playerXString.c_str();
			DrawText(playerX, 20, 130, 20, RED);

			// Debug print the player object global y location
			string playerYPositionString = to_string(init->playerObjectPtr->GlobalTransform().m12);
			string playerYString = "Player object y:	" + playerYPositionString;
			const char* playerY = playerYString.c_str();
			DrawText(playerY, 20, 160, 20, RED);

			// Debug print the player sprite global x location
			string spriteXPositionString = to_string(init->playerSpritePtr->GlobalTransform().m02);
			string spriteXString = "Player sprite x:	" + spriteXPositionString;
			const char* spriteX = spriteXString.c_str();
			DrawText(spriteX, 20, 190, 20, RED);

			// Debug print the player sprite global y location
			string spriteYPositionString = to_string(init->playerSpritePtr->GlobalTransform().m12);
			string spriteYString = "Player sprite y:	" + spriteYPositionString;
			const char* spriteY = spriteYString.c_str();
			DrawText(spriteY, 20, 210, 20, RED);

		// Enemy printouts
			// Debug print the number of enemies in the root objects
			string enemyRootObjectsString = to_string(enemyCount);
			string enemyRootString = "Root object enemies:	" + enemyRootObjectsString;
			const char* numEnemies_01 = enemyRootString.c_str();
			DrawText(numEnemies_01, 20, 240, 20, RED);
			
			// Debug print the number of enemies in their own vector
			string enemyObjectsString = to_string(enemies.size());
			string enemyString = "Enemy list enemies:	" + enemyObjectsString;
			const char* numEnemies_02 = enemyString.c_str();
			DrawText(numEnemies_02, 20, 270, 20, RED);

		// Base printouts
			// Debug print the number of bases in the root objects
			string baseRootObjectsString = to_string(baseCount);
			string baseRootString = "Root object bases:	" + baseRootObjectsString;
			const char* numBases_01 = baseRootString.c_str();
			DrawText(numBases_01, 20, 300, 20, RED);

			// Debug print the number of bases in their own vector
			string basesObjectsString = to_string(bases.size());
			string basesString = "Base list bases:	" + basesObjectsString;
			const char* numBases_02 = basesString.c_str();
			DrawText(numBases_02, 20, 330, 20, RED);
	


	//// Player base 1 global x location
	//float base_01_x = init->basePtr_01->GlobalTransform().m02;
	//std::string baseX = to_string(base_01_x);
	//const char* bX = baseX.c_str();

	//// Player base 1 global y location
	//float base_01_y = init->basePtr_01->GlobalTransform().m12;
	//std::string baseY = to_string(base_01_y);
	//const char* bY = baseY.c_str();

	//// Base printouts
	//DrawText(bX, 50, 250, 20, LIGHTGRAY);
	//DrawText(bY, 50, 300, 20, LIGHTGRAY);


	
	

	//std::cout << "Number of Root objects: " << rootObjects.size() << std::endl;
	//std::cout << "Number of Player objects: " << playerCount << std::endl;
	//std::cout << "Number of Enemy objects: " << enemyCount << std::endl;
	//std::cout << "Number of Base objects: " << baseCount << std::endl;
	//std::cout << "Number of Weapon objects: " << enemyAttackCount << std::endl;
	//std::cout << "Number of Weapon objects: " << friendlyAttackCount << std::endl;
	//std::cout << "Player weapon equipped: " << init->playerObjectPtr->GetWeapon() << std::endl;
	//DebugCheckWeapon();
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