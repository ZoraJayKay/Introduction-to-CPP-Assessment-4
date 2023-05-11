#pragma once
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <iostream>
#include <time.h>
#include "GameObject.h"

using namespace std;

class Game
{
private:
	//	https://learncplusplus.org/how-to-make-a-millisecond-timer-in-c-and-c/
	// 
	//	***		TIMER VARIABLES		***
	long currentTime = 0;   // for moment-in-time snapshots
	long lastTime = 0;      // time at first moment of an update
	float timer = 0;        // running timer of time spent updating
	int fps = 1;            // variable that holds the FPS for printing to the screen
	int frames;             // 
	int speed = 100;
	float deltaTime = 0.005f;
	clock_t start, end;		// this is a datatype defined by the standard time.h library, not me
	

protected:
	// a vector of parentless GameObjects
	vector<GameObject*> rootObjects;

	// a vector of GameObjects waiting to be added to the vector of parentless GameObjects between updates
	vector<GameObject*> rootObjectsToAdd;

	// a vector of GameObjects waiting to be removed from the vector of parentless GameObjects between updates
	vector<GameObject*> rootObjectsToRemove;

public: 
	// default constructor function
	Game();

	// default destructor function
	~Game();

	// TEST
	void PrintTime();

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

