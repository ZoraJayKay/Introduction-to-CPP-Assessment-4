#pragma once
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <iostream>

using namespace std;

class Game
{
private:
	// private stuff here (C++ classes are private by default)



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

	// 1.3: Update scene calculations
	void UpdateCalculations();

	// 1.4: Draw the scene
	void Draw();
		

	// 2: ENDIF FUNCTION
	void Shutdown();
			// 2.1: Detect whether the game has ended
};

