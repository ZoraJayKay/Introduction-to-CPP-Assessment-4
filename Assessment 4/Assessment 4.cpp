// Assessment 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"
#include "Game.h"


// the main function of the program starts and ends the game.
int main()
{
    // 1: Create a pointer to a new instance of a Game class. 
    Game* game = new Game();
        // The Game class instance (game) will in turn initialise a game, create the play area, draw the scene, and update the game calculations until the game ends.
        
    // 2: Keep the game running until the loss condtion is met.
    while (!WindowShouldClose()) 
    {
        game->Update();        
    }
        // This while loop keeps the game running for as long as the game does not meet the conditions to close the game. The Update function in the Game class performs

    game->Shutdown();
    CloseWindow();
}
