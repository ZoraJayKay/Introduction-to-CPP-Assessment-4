#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Game.h"
#include "Initialise.h"
#include "Timer.h"
#include "Controller.h"
#include <string>

// Program screen size
int screenWidth = 1080;
int screenHeight = 720;

// Play area variables
int playWidth = 1000;
int playHeight = 660;

// Timer variables
float targetFps = 60.0f;
float elapsedTime = 0.0f;
int frames = 0;

// 1: Initialise a game session (default constructor)
Game::Game() 
{
	std::cout << "---Game constructor---" << endl;
	
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

	SetTargetFPS(60);
}

Game::~Game() 
{
	// Delete the pointer for the initialisation process
	delete init;
	init = nullptr;

	// Delete all of the vectors of game object pointers for the game actors
	/*for (GameObject* obj : rootObjects) {
		delete obj;
		obj = nullptr;
	}*/
	// Above causing stack overflow on exit?

	for (GameObject* obj : rootObjectsToAdd) {
		delete obj;
		obj = nullptr;
	}

	for (GameObject* obj : rootObjectsToRemove) {
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
			// Debug();

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
		// for each pointer in the vector of objects to remove...
		for (GameObject* obj : rootObjectsToRemove) {
		
			// create an iterator which will find the pointer to remove in the rootObjects vector
			vector<GameObject*>::iterator itr = find(rootObjects.begin(), rootObjects.end(), obj);
		
			// save the position between index 0 and the found pointer
			int index = distance(rootObjects.begin(), itr);

			// erase the found pointer
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
	// score
	// lives
	
	// Create a string out of the player score
	std::string s = to_string(init->playerObjectPtr->score);
	// Create a const char pointer that points to the address of the string 's' as an array of characters
	const char* scr = s.c_str();
	
	DrawText("Score: " + *scr, 20, 20, 20, LIGHTGRAY);
	
	// 2.2.4.3: Draw all root objects (and thus their children)
	for (GameObject* obj : rootObjects) {
		// Call the Draw function that is defined in the GameObject class
		obj->Draw();
	}

	EndDrawing();
}


void Game::Debug() {
	int playerCount = 0;
	int enemyCount = 0;
	int baseCount = 0;

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

	std::cout << "Number of Root objects: " << rootObjects.size() << std::endl;
	std::cout << "Number of Player objects: " << playerCount << std::endl;
	std::cout << "Number of Enemy objects: " << enemyCount << std::endl;
	std::cout << "Number of Base objects: " << baseCount << std::endl;
}