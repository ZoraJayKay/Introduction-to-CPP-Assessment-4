#pragma once
//#include "raylib.h"
//#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_SUPPORT_ICONS
#include <iostream>
#include <time.h>
#include "GameObject.h"

using namespace std;

class Game
{
private:


protected:
	// a vector of parentless GameObjects
	vector<GameObject*> rootObjects;

	// a vector of GameObjects waiting to be added to the vector of parentless GameObjects between updates
	vector<GameObject*> rootObjectsToAdd;

	// a vector of GameObjects waiting to be removed from the vector of parentless GameObjects between updates
	vector<GameObject*> rootObjectsToRemove;

	float targetFps = 60.0f;
	float elapsedTime = 0.0f;
	int frames = 0;

public: 
	// default constructor function
	Game();

	// default destructor function
	~Game();


	// 0: Initialise a game session


	// 1: UPDATE FUNCTION
	void Update();

	// 1.1: Update the game timer
	void UpdateTimer();

	// 1.2: Update object relationships
	void UpdateRelationships();

	// 1.2.1: Add objects created since last update to the list of root objects
	void AddRootObject(GameObject& obj);

	// 1.2.2: Add objects targeted for removal since last update to a list
	void RemoveRootObject(GameObject& obj);

	// 1.3: Update scene calculations
	void UpdateCalculations();

	// 1.4: Draw the scene
	void Draw();
		

	// 2: ENDIF FUNCTION
	void Shutdown();
			// 2.1: Detect whether the game has ended
};

