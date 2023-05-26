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
		// A vector of all enemies
		vector<Enemy*> enemies;
		// A vector of enemy objects waiting to be added to the vector of enemies between updates
		vector<Enemy*> enemiesToAdd;
		// A vector of enemy objects waiting to be removed from the vector of enemies between updates
		vector<Enemy*> enemiesToRemove;

	//	*** ---	BASE OBJECT HIERARCHY --- ***
		// A vector of all bases
		vector<Base*> bases;
		// A vector of base objects waiting to be added to the vector of bases between updates
		vector<Base*> basesToAdd;
		// A vector of base objects waiting to be removed from the vector of bases between updates
		vector<Base*> basesToRemove;


	// Create a forward declaration of an initialisation class for the use of the Game
	class Initialise* init;

	// Create a forward declaration of a controller class for the use of the Game
	class Controller* cntrlr;

public: 
	// Timer instance
	class Timer* gameTimer;

	// Program screen size
	int screenWidth;
	int screenHeight;

	// Play area variables
	int playWidth;
	int playHeight;

	// 0: Initialise a game session (default constructor)
	Game();

	// default destructor function
	~Game();
		
	// 1: UPDATE FUNCTION
	void Update();	
		// 1.2.1: Update object relationships
		void UpdateRelationships();
			// 1.2.1.1: Add objects created since last update to the list of root objects
			void AddRootObject(GameObject& obj);
			// 1.2.1.2: Add objects targeted for removal since last update to a list
			void RemoveRootObject(GameObject& obj);
			// 1.2.1.3: Add enemy objects created since last update to the list of enemy objects
			void AddEnemyObject(Enemy& enemy);
			// 1.2.1.4: Add enemy objects targeted for removal since last update to a list
			void RemoveEnemyObject(Enemy& enemy);
			// 1.2.1.5: Add base objects created since last update to the list of base objects
			void AddBaseObject(Base& base);
			// 1.2.1.5: Add base objects targeted for removal since last update to a list
			void RemoveBaseObject(Base& base);

		// 1.2.2: Update scene calculations
		void UpdateCalculations();

		// 1.2.3: Draw the scene
		void Draw();
			// 1.2.3.1 Print the player score to the screen
			void PrintPlayerScore();
			// 1.2.3.2 Print the player's lives to the screen
			void PrintPlayerLives();

		// A temporary function for printing analysis to the console
		void Debug();
		void DebugCheckWeapon();

	// 2: ENDIF FUNCTION
	void Shutdown();
			// 2.1: Detect whether the game has ended
};

