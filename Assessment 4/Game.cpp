#include "Game.h"
#include "Initialise.h"
#include "Timer.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

// Play area variables
int screenWidth = 1080;
int screenHeight = 720;

// Timer variables
float targetFps = 60.0f;
float elapsedTime = 0.0f;
int frames = 0;

// 0: Initialise a game session (default constructor)
Game::Game() 
{
	std::cout << "---Game constructor---" << endl;
	
	// Print message in program banner at top of screen
	// NOTE TO SELF: InitWindow needs to be done BEFORE loading any textures
	InitWindow(screenWidth, screenHeight, "Zora Jane Kerr: Introduction to C++ (Assessment 4 - Retro Game) Space Invaders (AIE, 2023 [student year 1])");

	// 0: Initialise a game session
	// Create a pointer to a new instance of the Initialise class.
	// The Initialise class instance (init) will in turn set all of the parameters that constitute the starting conditions of the game.	
	Initialise* init = new Initialise();
	publicInit = init;

	// Add the starting objects to the scene as root objects
	AddRootObject(*(init->playerObject));
	// AddRootObject(*(init(enemy objects));
	// AddRootObject(*(init(base objects));

	SetTargetFPS(60);
}

// Game class destructor
Game::~Game() 
{

}



// 1: UPDATE FUNCTION
void Game::Update()
{
	// 1.1: Update the game timer
	// Instantiate a timer if one doesn't already exist
	gameTimer = Timer::Instance();

	// Update delta time
	gameTimer->Tick();

	// Reset the clock's 'start' timer
	gameTimer->Reset();

	// Increment the timer with delta time
	elapsedTime += gameTimer->DeltaTime();

	// Increment the frames
	frames++;

		if (elapsedTime >= gameTimer->DeltaTime()) {
			// print framerate
			// std::cout << frames / elapsedTime << endl;	

			UpdateRelationships();
			UpdateCalculations();
			Draw();
		}
}


// 1.2: Update object relationships
void Game::UpdateRelationships()
{
	//***	ADDING ROOT OBJECTS		***
		// for each pointer in the vector of objects to remove...
		for (GameObject* obj : rootObjectsToAdd) {
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

// 1.3: Update scene calculations
void Game::UpdateCalculations() 
{
	// reference the controller?
}

// 1.4: Draw the scene
void Game::Draw() 
{
	BeginDrawing();

	// 1.4.1: Create the visible play area
	ClearBackground(RAYWHITE);

	DrawText("Placeholder text", screenWidth / 2, screenHeight / 2, 20, LIGHTGRAY);

	// 1.4.2: Draw all root objects (and thus their children)
	for (GameObject* obj : rootObjects) {
		obj->Draw();
	}

	EndDrawing();
}
		

// 2: ENDIF FUNCTION
void Game::Shutdown() 
{
	delete this;
}