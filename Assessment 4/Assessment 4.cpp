// Assessment 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

#include "Game.h"
#include <iostream>
using namespace std;

// the main function of the program starts and ends the game.
int main()
{
    std::cout << "---Program constructor---" << endl;

    // 1: Create a pointer to a new instance of a Game class. 
    Game* game = new Game();
    // The Game class instance (game) will in turn initialise a game, create the play area, draw the scene, and update the game calculations until the game ends.

    // 2: Keep the game running until the loss condtion is met.
    // This while loop keeps the game running for as long as the game does not meet the conditions to close the game. The Update function in the Game class performs
    while (!WindowShouldClose()) 
    {
        // update the game
        game->Update();

        // draw the game
        game->Draw();
    }        

    // Destroy the game class instance
    game->Shutdown();

    // Close the program
    CloseWindow();

    return 0;
}
