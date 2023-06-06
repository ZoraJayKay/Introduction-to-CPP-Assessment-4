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

// 0: Initialise a game session (constructor)
Game::Game() 
{
	std::cout << "---Game constructor---" << endl;
	
	// Program screen size
	windowWidth = 1080;
	windowHeight = 720;

	// Play area variables
	playWidth = 1000;
	playHeight = 660;

	isPaused = false;

	// Initialise the window
	// Print message in program banner at top of screen
	// NOTE TO SELF: InitWindow needs to be done BEFORE loading any textures
	InitWindow(windowWidth, windowHeight, "Zora Jane Kerr: Introduction to C++ (Assessment 4 - Retro Game) Space Invaders (AIE, 2023 [student year 1])");

	// 0.1: Initialise a game session
		// Initialise the audio device
		InitAudioDevice();
			
		// Initialise a pointer to a new instance of the Initialise class. The Initialise class instance (init) will in turn set all of the parameters that constitute the starting conditions of the game.	
		init = new Initialise(windowWidth, windowHeight);
			// EXTRA WORK: SET DIFFICULTY LEVELS THROUGH OVERLOADED INIT
				// Add number of enemies to instantiate
				// Add number of bases to instantiate
				// Set up functions that do the above instead of manually doing each one god damn
				// Add difficulty level that sets all of the above etc?

	// 0.2: Add the objects from initialisation to the scene as root, enemy and base objects
		// 0.2.1: Add the player
		AddRootObject(*(init->playerObjectPtr));

		// 0.2.2: Add the vector of enemies from initialisation
			for (Enemy* enemy : init->enemiesToInitialise) {
				// Add enemies as root objects of the scene...	
				AddRootObject(*enemy);
				// ... and to their own vector of enemies
				AddEnemyObject(*enemy);
				}

		// 0.2.3: Add the vector of bases from initialisation
			for (Base* base : init->basesToInitialise) {
				// Add bases as root objects of the scene...	
				AddRootObject(*base);
				// ... and to their own vector of bases
				AddBaseObject(*base);
				}

		// 0.2.4: Add the vector of AABBs from initialisation
			for (AABB* aabb: init->AABBsToInitialise) {
				// Add AABBs as collider objects of the scene.
				AddAABBObject(*aabb);
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
		// 1.1.2: Increment delta time
		gameTimer->Tick();
		// 1.1.3: Reset the clock's 'start' timer
		gameTimer->Reset();
		// 1.1.4: Increment the timer with delta time
		elapsedTime += gameTimer->DeltaTime();
		// Increment the frames (may or may not be using a frame counter - not currently)
		frames++;

	// 1.2: Update the game (if unpaused)
		if (elapsedTime >= gameTimer->DeltaTime()) {
			// 1.2.1: Update the object hierarchy including adding and removing parent / child relationships
			UpdateRelationships();
			// 1.2.2: Update the arithmetic underlying movement and drawing for all objects
			UpdateCalculations();
			// 1.2.3: Debug if necessary
			Debug();
			// 1.2.4: Draw the game scene
			Draw();
		}

	// 1.3: Pause and unpause the game
		if (IsKeyPressed(KEY_P)) {
			if (isPaused == false) {
				gameTimer->TimeScale(0.0f);
				isPaused = true;
			}
			else {
				gameTimer->TimeScale(1.0f);
				isPaused = false;
			}
		}
}

void Game::UpdateObjectAdditions() {
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

//***	ADDING AABB OBJECTS		***
	// for each pointer in the vector of AABBs to add...
	for (AABB* aabb : AABBsToAdd) {
		// add the pointer to the object to the back of the vector of AABB objects
		AABBs.push_back(aabb);
	}
	// clear the add-pending objects vector
	AABBsToAdd.clear();
};

void Game::UpdateObjectRemovals() {};


void Game::UpdateBaseObjects() {};

void Game::UpdateAABBObjects() {};


// 1.2.1: Update the object hierarchy including adding and removing parent / child relationships
void Game::UpdateRelationships()
{
	UpdateObjectAdditions();
	UpdateObjectRemovals();
	


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

//***	REMOVING AABB OBJECTS		***		
	// BEFORE deleting the root object, remove AABBs from the list of AABBs
	// for each pointer in the vector of AABBs to remove...
	for (AABB* aabb : AABBsToRemove) {
		// create an iterator which will find the pointer to remove in the enemies vector
		vector<AABB*>::iterator itr_01 = find(AABBs.begin(), AABBs.end(), aabb);

		// save the position between index 0 and the found pointer
		int index = distance(AABBs.begin(), itr_01);

		// erase the found pointer from the vector
		AABBs.erase(AABBs.begin() + index);
	}
	// clear the remove-pending objects vector
	AABBsToRemove.clear();

// ***	REMOVING ROOT OBJECTS		***		
	// *** COLLISIONS ***
	// For every collision box in the vector of collision boxes... 
	for (AABB* collider : AABBs) {
		// ... if a given collider is a friendly projectile...
		if (collider->ownerObject->objType == GameObject::Friendly_Projectile_Type) {
			// ... then check through the vector of collision boxes...
			for (AABB* ship : AABBs) {
				// ... and if a sprite collision box is found (ship AABBs have the ship sprite as their owner)
				if (ship->ownerObject->objType == GameObject::Enemy_Sprite_Type) {
					// ... and if the projectile collider overlaps the ship's sprite collider...
					if (collider->Overlaps(*ship)) {
						// 1: Delete the AABB of the friendly projectile
						RemoveAABBObject(*collider);
						// 2: Delete the AABB of the enemy ship
						RemoveAABBObject(*ship);
						// 3: Delete the friendly projectile Weapon class object
						RemoveRootObject(*collider->ownerObject);
						// 4: Delete the parent Game Object of the enemy ship sprite
						RemoveRootObject(ship->ownerObject->GetParent());
						// Haven't currently implemented removal from Enemy vector; uncertain if I really need it as a collection
					}
				};
			};
		};

		// ... if a given collider is an enemy projectile...
		if (collider->ownerObject->objType == GameObject::Enemy_Projectile_Type) {
			// ... then check through the vector of collision boxes...
			for (AABB* ship : AABBs) {
				// ... and if a friendly sprite collision box is found (ship AABBs have the ship sprite as their owner)
				if (ship->ownerObject->objType == GameObject::Friendly_Sprite_Type) {
					// ... and if the projectile collider overlaps the ship's sprite collider...
					if (collider->Overlaps(*ship)) {
						// 1: Decrement player lives
						init->playerObjectPtr->lives--;
						// 2: Delete the AABB of the enemy projectile
						RemoveAABBObject(*collider);
						// 3: Delete the enemy projectile Weapon class object
						RemoveRootObject(*collider->ownerObject);
					};
				};
			};
		}
	};

		// B: Add any objects that have left the play area to the list to delete
			// for each pointer in the vector of objects to remove...
			for (GameObject* obj : rootObjects) {
				if (
					// I removed x-axis destruction because the controller prevents ships moving off the x-axis; unnecessary calculation.
					//// if x axis is off the width, or...
					//(obj->GlobalTransform().m02 < 0 || obj->GlobalTransform().m02 > windowWidth) ||
					// if y axis is off the height...
					(obj->GlobalTransform().m12 < 0 || obj->GlobalTransform().m12 > windowHeight))
				{					
					// Add the object to the list of objects to remove
					RemoveRootObject(*obj);
					// Add the object's collider to the list of AABBs to remove
					RemoveAABBObject(*obj->colliderPtr);
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
};


// 1.2.2: Update the arithmetic underlying movement and drawing
void Game::UpdateCalculations()
{
	// Update the calculations for all root objects (and thus their children)
	for (GameObject* obj : rootObjects) {
		// Call the Update function that is defined in the GameObject class
		obj->Update(gameTimer->DeltaTime() * gameTimer->GetTimeScale(), *cntrlr);
	}
};


// 1.2.4: Draw the game scene
void Game::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// 1.2.4.1: Draw all root objects (and thus their children)
	for (GameObject* obj : rootObjects) {
		// Call the Draw function that is defined in the GameObject class
		obj->Draw();
	}

	// 1.2.4.2 Print the player score to the screen
	PrintPlayerScore();
	// 1.2.4.3 Print the player's lives to the screen
	PrintPlayerLives();

	EndDrawing();
};



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

// 1.2.1.6: Add collider objects created since last update to the list of collider objects
void Game::AddAABBObject(AABB& aabb) {
	// Create a pointer of the object reference passed in 
	AABB* AABBPtr = &aabb;
	// Add the new pointer to the object passed in to the vector
	AABBsToAdd.push_back(AABBPtr);
};

// 1.2.1.7: Add collider objects targeted for removal since last update to a list
void Game::RemoveAABBObject(AABB& aabb) {
	// Create a pointer of the object reference passed in 
	AABB* AABBPtr = &aabb;
	// Add the new pointer to the object passed in to the vector
	AABBsToRemove.push_back(AABBPtr);
};





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

// 9: Destructor
Game::~Game()
{
	// The timer is destroyed by the Main function after the Game class is destroyed.

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

	// Delete all of the vectors of collider pointers
	for (AABB* aabb : AABBsToAdd) {
		delete aabb;
		aabb = nullptr;
	}

	for (AABB* aabb : AABBsToRemove) {
		delete aabb;
		aabb = nullptr;
	}

	for (AABB* aabb : AABBs) {
		delete aabb;
		aabb = nullptr;
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

	int AABB_Count = 0;
	int AABB_Friendly_Count = 0;
	int AABB_Enemy_Count = 0;
	int AABB_EnemyShip_Count = 0;
	int AABB_Player_Count = 0;
	int AABB_Sprite_Count = 0;
	int AABB_GameObject_Count = 0;
	int AABB_Default_Count = 0;

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

		// CONSOLE DEBUG: COUNT THE AABB OBJECTS IN THEIR OWN VECTOR
		for (AABB* aabb : AABBs) {
			AABB_Count++;
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

		// CONSOLE DEBUG: COUNT THE FRIENDLY PROJECTILE OBJECTS IN AABBS
		for (AABB* aabb : AABBs) {
			if (aabb->ownerObject->objType == GameObject::Friendly_Projectile_Type) {
				AABB_Friendly_Count++;
			}
		}

		// CONSOLE DEBUG: COUNT THE ENEMY PROJECTILE OBJECTS IN AABBS
		for (AABB* aabb : AABBs) {
			if (aabb->ownerObject->objType == GameObject::Enemy_Projectile_Type) {
				AABB_Enemy_Count++;
			}
		}

		// CONSOLE DEBUG: COUNT THE ENEMY SHIP OBJECTS IN AABBS
		for (AABB* aabb : AABBs) {
			if (aabb->ownerObject->objType == GameObject::Enemy_Type) {
				AABB_EnemyShip_Count++;
			}
		}

		// CONSOLE DEBUG: COUNT THE ENEMY SHIP OBJECTS IN AABBS
		for (AABB* aabb : AABBs) {
			if (aabb->ownerObject->objType == GameObject::Player_Type) {
				AABB_Player_Count++;
			}
		}

		// CONSOLE DEBUG: COUNT THE SPRITE OBJECTS IN AABBS
		for (AABB* aabb : AABBs) {
			if (aabb->ownerObject->objType == GameObject::Sprite_Type) {
				AABB_Sprite_Count++;
			}
		}

		//// CONSOLE DEBUG: COUNT THE GAMEOBJECT OBJECTS IN AABBS
		//for (AABB* aabb : AABBs) {
		//	if (aabb->ownerObject->) {
		//		AABB_Sprite_Count++;
		//	}
		//}

		// CONSOLE DEBUG: COUNT THE DEFAULT OBJECTS IN AABBS
		for (AABB* aabb : AABBs) {
			if (aabb->ownerObject->objType == GameObject::Default_Type) {
				AABB_Sprite_Count++;
			}
		}


	// DEBUG PRINTOUTS			
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
	
		// Root object printouts
			// Debug print the total number of root objects
			string rootObjectString = to_string(rootObjects.size());
			string rootString = "Total root objects:	" + rootObjectString;
			const char* rootS = rootString.c_str();
			DrawText(rootS, 20, 360, 20, RED);

		// Debug print the number of AABBs in their own vector
			string AABBObjectsString = to_string(AABBs.size());
			string AABBsString = "AABB list AABBs:	" + AABBObjectsString;
			const char* numAABBs = AABBsString.c_str();
			DrawText(numAABBs, 20, 390, 20, RED);

		// Debug print the number of friendly fire AABBs in their own vector
			string friendlyAABBObjectsString = to_string(AABB_Friendly_Count);
			string friendlyAABBsString = "AABB list friendly projectiles:	" + friendlyAABBObjectsString;
			const char* friendlyNumAABBs = friendlyAABBsString.c_str();
			DrawText(friendlyNumAABBs, 20, 420, 20, RED);

		// Debug print the number of enemy fire AABBs in their own vector
			string enemyAABBObjectsString = to_string(AABB_Enemy_Count);
			string enemyAABBsString = "AABB list enemy projectiles:	" + enemyAABBObjectsString;
			const char* enemyNumAABBs = enemyAABBsString.c_str();
			DrawText(enemyNumAABBs, 20, 450, 20, RED);

		// Debug print the number of enemy ship AABBs in their own vector
			string enemyShipAABBObjectsString = to_string(AABB_EnemyShip_Count);
			string enemyShipAABBsString = "AABB list enemy ships:	" + enemyShipAABBObjectsString;
			const char* enemyShipNumAABBs = enemyShipAABBsString.c_str();
			DrawText(enemyShipNumAABBs, 20, 480, 20, RED);

		// Debug print the number of player ship AABBs in their own vector
			string playerShipAABBObjectsString = to_string(AABB_Player_Count);
			string playerShipAABBsString = "AABB list player ships:	" + playerShipAABBObjectsString;
			const char* playerShipNumAABBs = playerShipAABBsString.c_str();
			DrawText(playerShipNumAABBs, 20, 510, 20, RED);

		// Debug print the number of sprite AABBs in their own vector
			string spriteAABBObjectsString = to_string(AABB_Sprite_Count);
			string spriteAABBsString = "AABB list sprite items:	" + spriteAABBObjectsString;
			const char* spriteNumAABBs = spriteAABBsString.c_str();
			DrawText(spriteNumAABBs, 20, 540, 20, RED);

		// Debug print the number of default AABBs in their own vector
			string defaultAABBObjectsString = to_string(AABB_Default_Count);
			string defaultAABBsString = "AABB list default items:	" + defaultAABBObjectsString;
			const char* defaultNumAABBs = defaultAABBsString.c_str();
			DrawText(defaultNumAABBs, 20, 570, 20, RED);
}

void Game::DebugCheckWeapon() {
	switch (init->playerObjectPtr->GetWeapon()) {
	case 0:	
		std::cout << "Laser equipped" << std::endl;
		break;

	case 1:
		std::cout << "Double laser equipped" << std::endl;
		break;

	case 2:
		std::cout << "Weapon not equipped" << std::endl;
		break;

	case 3:
		std::cout << "Weapon not equipped" << std::endl;
		break;
	}
};