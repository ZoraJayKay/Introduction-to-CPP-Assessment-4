#pragma once

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

#include "Game.h"
#include <iostream>
#include "Timer.h"

using namespace std;
using namespace Utilities;

int main()
{
    std::cout << "---Program constructor---" << endl;

    // 1: Create a pointer to a new instance of a Game class. 
    // The Game class instance (game) will in turn initialise a game, create the play area, draw the scene, and update the game calculations until the game ends.
    Game* game = new Game();

    // 2: Keep the game running until the loss condition is met.
    // This while loop keeps the game running for as long as the game does not meet the conditions to close the game.
    while (!WindowShouldClose()) 
    {
        // 2.1: Update the game, its calculations, and draw to the screen
        game->Update();
    }        

    // 3: Shutdown
        // 3.1: Destroy the timer
        Utilities::Timer::Release();

        // 3.2: Close the audio device started in Game
        CloseAudioDevice();

        // 3.3: Destroy the game class instance
        delete game;
        game = nullptr;

        // 3.4: Close the program
        CloseWindow();

    return 0;
}
