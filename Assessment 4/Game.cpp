#include "Game.h"
#include "Initialise.h"
#include "Timer.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

// Below are my member function constructor and destructor. 

// Note to self: These don't have return types like in C#. They belong to an instance of the class.
// (class) (scope resolution operator) (function)
// Game::Game()


// Play area variables
int screenWidth = 800;
int screenHeight = 450;



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


Game::~Game() 
{

}



// 1: UPDATE FUNCTION
// 1.1: Update the game timer
void Game::Update()
{	
	// Instantiate a timer
	Utilities::Timer* timer = Utilities::Timer::Instance();

	// Recognise that the timer is running
	bool isRunning = true;

	// While the clock is running...
	while (isRunning) {
		// increment the timer with the Tick function...
		timer->Tick();
		timer->Reset();
		elapsedTime += timer->DeltaTime();
		frames++;


		if (elapsedTime >= 1.0f) {
			//std::cout << elapsedTime << endl;	// framerate
			std::cout << timer->DeltaTime() << std::endl;	// time taken per tick

			UpdateRelationships();
			UpdateCalculations();
			Draw();
			//elapsedTime -= 1;
			frames = 0;
		}
	}

	Utilities::Timer::Release();
}


// 1.2: Update object relationships
void Game::UpdateRelationships()
{

}

// 1.3: Update scene calculations
void Game::UpdateCalculations() 
{

}

// 1.4: Draw the scene
void Game::Draw() 
{
	// 1: Create the visible play area
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Placeholder text", screenWidth / 2, screenHeight / 2, 20, LIGHTGRAY);

	EndDrawing();
}
		

// 2: ENDIF FUNCTION
void Game::Shutdown() 
{
	delete this;
}