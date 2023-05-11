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

    // 1: Create the visible play area
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Zora Jane Kerr: Introduction to C++ (Assessment 4 - Retro Game) Space Invaders (AIE, 2023 [student year 1])");

    SetTargetFPS(60);
    
    // 2: Create a pointer to a new instance of a Game class. 
    Game* game = new Game();
    // The Game class instance (game) will in turn initialise a game, create the play area, draw the scene, and update the game calculations until the game ends.

    // 3: Keep the game running until the loss condtion is met.
    while (!WindowShouldClose()) 
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Placeholder text", screenWidth / 2, screenHeight / 2, 20, LIGHTGRAY);

        EndDrawing();

        // game->Update();        
    }
        // This while loop keeps the game running for as long as the game does not meet the conditions to close the game. The Update function in the Game class performs

    // game->Shutdown();
    CloseWindow();

    return 0;
}
