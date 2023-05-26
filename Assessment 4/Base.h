#pragma once
#include "GameObject.h"

class Base : public GameObject
{
public:
	Base();
	Base(float xPosition, float yPosition);
	~Base();

	// Position on the screen to start drawing the top-left of the base (0,0 would be top left of the scene)
	float xPos;
	float yPos;

	// Base object variables for a 256 x 256 objects
	// Array row and column volumes
	static const int ROWS = 8;
	static const int COLS = 8;

	// Base array
	int tiles[ROWS * COLS];

	// Array individual tile sizes
	int tileWidth = 32;
	int tileHeight = 32;

	// Object for iterating through the memory allocation of the array
	size_t arraySize;

	//size_t GetArraySize();
	void LoadBase();

	//	*** DRAWING FUNCTIONS	***
	// definition to override the OnDraw from parent GameObject so that the sprite source file can use OnDraw with sprite texture
	void OnDraw() override;

	Color GetTileColour(int tileValue);
};

