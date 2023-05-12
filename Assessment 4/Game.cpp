#include "Game.h"
#include "Initialise.h"
#include "Timer.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

// Play area variables
int screenWidth = 800;
int screenHeight = 450;

// Timer variables
float targetFps = 60.0f;
float elapsedTime = 0.0f;
int frames = 0;

// Game class constructor
Game::Game() 
{
	std::cout << "---Game constructor---" << endl;
	
	// 0: Initialise a game session
	// Create a pointer to a new instance of the Initialise class.
	Initialise* init = new Initialise();
	// The Initialise class instance (init) will in turn set all of the parameters that constitute the starting conditions of the game.	

	// Print banner at top of screen
	InitWindow(screenWidth, screenHeight, "Zora Jane Kerr: Introduction to C++ (Assessment 4 - Retro Game) Space Invaders (AIE, 2023 [student year 1])");

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
	Utilities::Timer* timer = Utilities::Timer::Instance();

	// Update delta time
	timer->Tick();

	// Reset the clock's 'start' timer
	timer->Reset();

	// Increment the timer with delta time
	elapsedTime += timer->DeltaTime();

	// Increment the frames
	frames++;

		if (elapsedTime >= timer->DeltaTime()) {
			std::cout << frames / elapsedTime << endl;	// framerate
			//std::cout << timer->DeltaTime() << std::endl;	// time taken per tick
			//frames = 0;
			//elapsedTime -= 1;

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

		rootObjectsToRemove.clear();
		// clear the remove-pending objects vector

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


	// 1.4.2: Render objects
	// fill

	EndDrawing();
}
		

// 2: ENDIF FUNCTION
void Game::Shutdown() 
{
	delete this;
}