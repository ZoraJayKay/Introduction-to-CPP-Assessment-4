#include "Game.h"
#include "Initialise.h"

// Below are my member function constructor and destructor. These don't have return types like in C#. They belong to an instance of the class.
// (class) (scope resolution operator) (function)
// Game::Game()

Game::Game() 
{
	std::cout << "---Game constructor---" << endl;
	PrintTime();
	// 0: Initialise a game session
	// Create a pointer to a new instance of the Initialise class.
	Initialise* init = new Initialise();
	// The Initialise class instance (init) will in turn set all of the parameters that constitute the starting conditions of the game.	
}

void Game::PrintTime() {
	start = clock();	// start time
	
	end = clock();		// end time
	std::cout << "The time was " << (end - start) / CLK_TCK << endl;
}

Game::~Game() 
{

}



// 1: UPDATE FUNCTION
void Game::Update()
{	
	UpdateTimer();
	UpdateRelationships();
	UpdateCalculations();
	Draw();
}

// 1.1: Update the game timer
void Game::UpdateTimer()
{
	// take a time snapshot at the moment of update
			// *** FIX
	//currentTime = stopwatch.ElapsedMilliseconds;
	// calculate time elapsed since last update
	deltaTime = (currentTime - lastTime) / 1000.0f;
	
	// add the time since last update to a timer
	timer += deltaTime;	

	if (timer >= 1)
	{
		fps = frames;
		frames = 0;
		timer -= 1;
	}
	frames++;
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

}
		

// 2: ENDIF FUNCTION
void Game::Shutdown() 
{
	// 2.1: Detect whether the game has ended
}