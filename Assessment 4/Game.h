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
	// A vector of parentless GameObjects
	vector<GameObject*> rootObjects;

	// A vector of GameObjects waiting to be added to the vector of parentless GameObjects between updates
	vector<GameObject*> rootObjectsToAdd;

	// A vector of GameObjects waiting to be removed from the vector of parentless GameObjects between updates
	vector<GameObject*> rootObjectsToRemove;

	// Create a forward declaration of an initialisation class for the use of the Game
	class Initialise* init;

	// Create a forward declaration of a controller class for the use of the Game
	class Controller* cntrlr;

public: 
	// Timer instance
	class Timer* gameTimer;

	// 0: Initialise a game session (default constructor)
	Game();

	// default destructor function
	~Game();
		
	// 1: UPDATE FUNCTION
	void Update();	// 1.1: Update the game timer

	// 1.2: Update object relationships
	void UpdateRelationships();

	// 1.2.1: Add objects created since last update to the list of root objects
	void AddRootObject(GameObject& obj);

	// 1.2.2: Add objects targeted for removal since last update to a list
	void RemoveRootObject(GameObject& obj);

	// 1.3: Update scene calculations
	void UpdateCalculations();

	// 1.4: Draw the scene
	void Draw();	// includes...
	// 1.4.1: Create the visible play area
	// 1.4.2: Render objects
	
	// A temporary function for printing analysis to the console
	void Debug();
	void DebugCheckWeapon();

	// 2: ENDIF FUNCTION
	void Shutdown();
			// 2.1: Detect whether the game has ended
};

