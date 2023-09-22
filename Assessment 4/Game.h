#pragma once

#include <iostream>
#include "GameObject.h"
#include "Initialise.h"
#include "Timer.h"

using namespace Utilities;
using namespace std;

class Game
{
private:


protected:
	//	*** ---	ROOT OBJECT HIERARCHY --- ***
		// A vector of parentless GameObjects
		vector<GameObject*> rootObjects;
		// A vector of GameObjects waiting to be added to the vector of parentless GameObjects between updates
		vector<GameObject*> rootObjectsToAdd;
		// A vector of GameObjects waiting to be removed from the vector of parentless GameObjects between updates
		vector<GameObject*> rootObjectsToRemove;

	//	*** ---	ENEMY OBJECT HIERARCHY --- ***
		// Simple variable for win/loss criteria
		int numberOfEnemies;
		int startingEnemies = 3;
		int spawnIncrement = 3;
	
	// NOT IN USE
		//// A vector of all enemies
		//vector<Enemy*> enemies;
		//// A vector of enemy objects waiting to be added to the vector of enemies between updates
		//vector<Enemy*> enemiesToAdd;
		//// A vector of enemy objects waiting to be removed from the vector of enemies between updates
		//vector<Enemy*> enemiesToRemove;

	//	*** ---	BASE OBJECT HIERARCHY --- ***
		// A vector of all bases
		vector<Base*> bases;
		// A vector of base objects waiting to be added to the vector of bases between updates
		vector<Base*> basesToAdd;
		// A vector of base objects waiting to be removed from the vector of bases between updates
		vector<Base*> basesToRemove;

	//	*** --- AABB OBJECT HIERARCHY --- ***
		// A vector of all bases
		vector<AABB*> AABBs;
		// A vector of base objects waiting to be added to the vector of bases between updates
		vector<AABB*> AABBsToAdd;
		// A vector of base objects waiting to be removed from the vector of bases between updates
		vector<AABB*> AABBsToRemove;
		// An iterator for collision detection
		//AABB* AABBiterator = new AABB;


	// Create a forward declaration of an initialisation class for the use of the Game
	class Initialise* init;

	// Create a forward declaration of a controller class for the use of the Game
	class Controller* cntrlr;

	int startingLives = 1;

public: 
	// Timer instance
	class Timer* gameTimer;

	// For giving the player time to read instructions at the beginning
	bool gameHasStarted = false;
	bool isPaused;

	// Program screen size
	int windowWidth;
	int windowHeight;

	// Play area variables
	int playWidth;
	int playHeight;
	
	// 0: Initialise a game session (constructor)
	Game();
	void CreateGame();
		// 0.1: Initialise a game session
		// 0.2: Add the objects from initialisation to the scene as root, enemy and base objects
			// 0.2.1: Add the player
			// 0.2.2 - 0.2.4
			void InitialiseGame(bool enemies, bool bases);
			// 0.2.2: Add the vector of enemies from initialisation
			// 0.2.3: Add the vector of bases from initialisation
			// 0.2.4: Add the vector of AABBs from initialisation
		// 0.3 - 0.4: 
		void InitialiseController();
		// 0.3: Initialise a pointer to a new instance of the Controller class.
		// 0.4 Permit the controller to make use of a game class pointer so that the controller can access the object hierarchy for instantiating weapon attacks
		// 0.5 Run the intro before the game starts proper (explain keybindings, objective)
		void RunIntro();

	// 9: Destructor
	~Game();
		
	// 1: UPDATE FUNCTION
	void Update();	
		// 1.1: Update the game timer
			// 1.1.1: Instantiate a timer if one doesn't already exist
			// 1.1.2: Increment delta time
			// 1.1.3: Reset the clock's 'start' timer
			// 1.1.4: Increment the timer with delta time
			// Increment the frames (may or may not be using a frame counter - not currently)
			
		// 1.2: Update the game (if unpaused)
			// 1.2.1: Update the object hierarchy including adding and removing parent / child relationships
				void UpdateRelationships();
				// 1.2.1.1: Add objects to the hierarchy
					void UpdateObjectAdditions();
						// 1.2.1.1.1: Update root object additions
						void UpdateRootObjectAdditions();
						// 1.2.1.1.2: Update enemy object additions
						// Not currently used
						// void UpdateEnemyObjectAdditions();
						// 1.2.1.1.3: Update base object additions
						void UpdateBaseObjectAdditions();
						// 1.2.1.1.4: Update AABB object additions
						void UpdateAABBObjectAdditions();

				// 1.2.1.2: Remove objects from the hierarchy
					void UpdateObjectRemovals();
						// 1.2.1.2.1 Update enemy object removals
						// Not currently used
						//void UpdateEnemyObjectRemovals();
						// 1.2.1.2.2 Update base object removals
						void UpdateBaseObjectRemovals();
						// 1.2.1.2.3 Update AABB object removals
						void UpdateAABBObjectRemovals();
						// 1.2.1.2.4 Update root object removals
						void UpdateRootObjectRemovals();
						// 1.2.1.2.5 Update collisions
						void UpdateCollisions();

				// 1.2.1.1: Add objects created since last update to the list of root objects
				void AddRootObject(GameObject& obj);
				// 1.2.1.2: Add objects targeted for removal since last update to a list
				void RemoveRootObject(GameObject& obj);
				// 1.2.1.3: Add enemy objects created since last update to the list of enemy objects
				//void AddEnemyObject(Enemy& enemy);
				// 1.2.1.4: Add enemy objects targeted for removal since last update to a list
				//void RemoveEnemyObject(Enemy& enemy);
				// 1.2.1.5: Add base objects created since last update to the list of base objects
				void AddBaseObject(Base& base);
				// 1.2.1.5: Add base objects targeted for removal since last update to a list
				void RemoveBaseObject(Base& base);
				// 1.2.1.6: Add collider objects created since last update to the list of collider objects
				void AddAABBObject(AABB& base);
				// 1.2.1.7: Add collider objects targeted for removal since last update to a list
				void RemoveAABBObject(AABB& base);

			// 1.2.2: Update the arithmetic underlying movement and drawing for all objects
				void UpdateCalculations();

			// 1.2.3: Debug if necessary
				void Debug();
				//void DebugCheckWeapon();

		// 1.3: Pause and unpause the game
			// 1.3.1: A function for deciding whether to pause or not
			void Pause();
			
			// 1.3.2: Pause the game
			void StopGame();
			
			// 1.3.3: Pause the game for a duration
			void StopGame(int duration);

			// 1.3.4: Resume the game
			void ResumeGame();


			// 1.2.4: Draw the scene
				// 1.2.4.1: Draw all root objects (and thus their children)
				void Draw();
				// 1.2.4.2 Print the player score to the screen
				void PrintPlayerScore();
				// 1.2.4.3 Print the player's lives to the screen
				void PrintPlayerLives();

			

	// 2: ENDIF FUNCTION
	// void Shutdown();  // Not performed within Game function currently
		// 2.1: Detect whether the game has ended	
};