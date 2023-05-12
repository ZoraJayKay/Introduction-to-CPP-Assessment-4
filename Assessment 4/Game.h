#pragma once
//#include "raylib.h"
//#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_SUPPORT_ICONS
#include <iostream>
#include "GameObject.h"

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

public: 
	// default constructor function
	Game();

	// default destructor function
	~Game();


	// 0: Initialise a game session


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
		

	// 2: ENDIF FUNCTION
	void Shutdown();
			// 2.1: Detect whether the game has ended
};

