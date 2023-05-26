#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Base.h"
#include <iostream>

// Default constructor
Base::Base() {};

// Overloaded constructor that permits setting the starting location of the base
Base::Base(float screenWidth, float screenHeight) {
	std::cout << "---Base constructor---" << std::endl;
	// Position on the screen to start drawing (0,0 would be top left of the screen)
	//xPos = screenWidth;
	//yPos = screenHeight;

	LoadBase();
	objType = Base_Type;

	xPos = 0;
	yPos = 0;
};

// Destructor
Base::~Base() {};


void Base::LoadBase() {
	arraySize = sizeof(tiles) / sizeof(tiles[0]);

	for (size_t i = 0; i < arraySize; i++) {
		tiles[i] = 2;	// Green temporarily for debugging
		/* load the stored 256x256 base texture */
	}
};

void Base::OnDraw() {
	// *** Currently bases aren't sprite objects and don't have textures ***
	// Set starting position for where the base will be drawn
	xPos = 0;
	yPos = 0;

	// For each element in the row (called y) of the array...
	for (int y = 0; y < ROWS; y++) {
		// Cycle through the elements in that column (called x)...
		for (int x = 0; x < COLS; x++) {
			// and make that element of the array become a tile of the given width and height.
			xPos = x * tileWidth;
			yPos = y * tileHeight;

			// Allocate the element and its tile a number...
			int indexCounter = (y * ROWS) + x;
			// Colour that element's tile...
			Color colour = GetTileColour(tiles[indexCounter]);
			// ... and draw that element's tile at its position in the world
			DrawRectangle(
				this->GlobalTransform().m02,	// Global x coordinate
				this->GlobalTransform().m12,	// Global y coordinate
				tileWidth,						// Width of 1 tile
				tileHeight,						// Height of 1 tile
				colour);						// Colour of this tile
		}
	}
};

Color Base::GetTileColour(int tileValue)
{
	switch (tileValue)
	{
	case 0: return WHITE;
	case 1: return RED;
	case 2: return GREEN;
	case 3: return BLUE;
	case 4: return YELLOW;
	}

	return BLACK;
}