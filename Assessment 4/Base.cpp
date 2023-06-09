#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Base.h"
#include <iostream>
#include "AABB.h"
#include <string>

// Default constructor
Base::Base() {};

// Overloaded constructor that permits setting the starting location of the base
Base::Base(float screenWidth, float screenHeight) {
	std::cout << "---Base constructor---" << std::endl;

	LoadBase();
	this->objType = Base_Type;

	xPos = 0;
	yPos = 0;
};

// Destructor
Base::~Base() {};


void Base::LoadBase() {
	// Find the size of the array
	arraySize = sizeof(tiles) / sizeof(tiles[0]);

	// For each element in the array...
	for (size_t i = 0; i < arraySize; i++) {
		// Set colour as green temporarily for debugging
		tiles[i] = 2;	
		// Create 1 GameObject for each element in the array
		GameObject* tile = new GameObject;
		// Make the GameObject of this element the 'base' type
		tile->objType = Base_Block_Type;
		// Make the collider of this GameObject an AABB of the parent base
		this->AddChild(*tile);
		this->AddAABBObject(*tile->colliderPtr);
		
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
			//Color colour = GetTileColour(tiles[indexCounter]);
			//// ... and draw that element's tile at its position in the world
			//DrawRectangle(
			//	this->GlobalTransform().m02 + xPos,	// Draw each rectangle at the base's global x coordinate PLUS this tile
			//	this->GlobalTransform().m12 + yPos,	// Draw each rectangle at the base's global y coordinate PLUS this tile
			//	tileWidth,						// Width of 1 tile
			//	tileHeight,						// Height of 1 tile
			//	colour);						// Colour of this tile


			//	*** COLLISION DETECTION	***
			// Update collider boundaries
			// AABB min:
			MyVector3* tempV1 = new MyVector3(
				(this->GlobalTransform().m02 + xPos),
				(this->GlobalTransform().m12 + yPos),
				0.0f);

			// AABB max:
			MyVector3* tempV2 = new MyVector3(
				(this->GlobalTransform().m02 + xPos + tileWidth),
				(this->GlobalTransform().m12 + yPos + tileHeight),
				0.0f);

			// Update the AABB of this specific tile using AABB min and max
			tileColliders[indexCounter]->UpdateBoxBoundries(*tempV1, *tempV2);

			Debug();
		}
	}
};

//void Base::UpdateColliderBoundaries() {
//	// *** Currently bases aren't sprite objects and don't have textures ***
//	// Set starting position for where the base will be drawn
//	xPos = 0;
//	yPos = 0;
//
//	// For each element in the row (called y) of the array...
//	for (int y = 0; y < ROWS; y++) {
//		// Cycle through the elements in that column (called x)...
//		for (int x = 0; x < COLS; x++) {
//			// and make that element of the array become a tile of the given width and height.
//			xPos = x * tileWidth;
//			yPos = y * tileHeight;
//
//			// Allocate the element and its tile a number...
//			int indexCounter = (y * ROWS) + x;
//
//			//	*** COLLISION DETECTION	***
//			// Update collider boundaries
//			// AABB min:
//			MyVector3* tempV1 = new MyVector3(
//				(this->GlobalTransform().m02 + xPos),
//				(this->GlobalTransform().m12 + yPos),
//				0.0f);
//
//			// AABB max:
//			MyVector3* tempV2 = new MyVector3(
//				(this->GlobalTransform().m02 + xPos + tileWidth),
//				(this->GlobalTransform().m12 + yPos + tileHeight),
//				0.0f);
//
//			// Update the AABB of this specific tile using AABB min and max
//			tileColliders[indexCounter]->UpdateBoxBoundries(*tempV1, *tempV2);
//
//			Debug();
//		}
//	}
//}


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

//	*** COLLISION DETECTION	***
// 1.2.1.6: Add collider objects created since last update to the list of collider objects
void Base::AddAABBObject(AABB& baseCollider) {
	// Create a pointer of the object reference passed in 
	AABB* AABBPtr = &baseCollider;
	// Add the new pointer to the object passed in to the vector
	tileCollidersToAdd.push_back(AABBPtr);
};

// 1.2.1.7: Add collider objects targeted for removal since last update to a list
void Base::RemoveAABBObject(AABB& baseCollider) {
	// Create a pointer of the object reference passed in 
	AABB* AABBPtr = &baseCollider;
	// Add the new pointer to the object passed in to the vector
	tileCollidersToRemove.push_back(AABBPtr);
};

void Base::OnUpdate(float deltaTime, Controller& ctrlr) {
	//***	ADDING AABB OBJECTS		***
	// for each pointer in the vector of AABBs to add...
	for (AABB* aabb : tileCollidersToAdd) {
		// add the pointer to the object to the back of the vector of AABB objects
		tileColliders.push_back(aabb);
	}
	// clear the add-pending objects vector
	tileCollidersToAdd.clear();

	//***	REMOVING AABB OBJECTS		***		
		// BEFORE deleting the root object, remove AABBs from the list of AABBs
		// for each pointer in the vector of AABBs to remove...
	for (AABB* aabb : tileCollidersToRemove) {
		// create an iterator which will find the pointer to remove in the enemies vector
		vector<AABB*>::iterator itr_01 = find(tileColliders.begin(), tileColliders.end(), aabb);

		// save the position between index 0 and the found pointer
		int index = distance(tileColliders.begin(), itr_01);

		// erase the found pointer from the vector
		tileColliders.erase(tileColliders.begin() + index);
	}
	// clear the remove-pending objects vector
	tileCollidersToRemove.clear();



	for (AABB* collider : tileColliders) {
		this->colliderPtr->debugBox2D(RED);
	};
}


void Base::Debug() {
	// CONSOLE DEBUG: COUNT THE PLAYER OBJECTS
	// This count will run for each base but then reset each time a new base gets calculated...
	int baseCount = 0;

	for (AABB* colliders : tileColliders) {
		if (colliders->ownerObject->objType == GameObject::Base_Block_Type) {
			//std::cout << colliders->ownerObject->objType << std::endl;
			baseCount++;
		}
	};

	// Debug print the number of default AABBs in their own vector
	string defaultAABBObjectsString = to_string(baseCount);
	string defaultAABBsString = "Number of colliders in all bases:	" + defaultAABBObjectsString;
	const char* defaultNumAABBs = defaultAABBsString.c_str();
	DrawText(defaultNumAABBs, 20, 630, 20, RED);



	//// Debug print the player object global x location
	//string AABB1XPositionString = to_string(tileColliders[0]->ownerObject->GlobalTransform().m02);
	//string AABBXString = "Base AABB1 x coords:	" + AABB1XPositionString;
	//const char* AABBX = AABBXString.c_str();
	//DrawText(AABBX, 20, 660, 20, RED);

	//// Debug print the player object global y location
	//string AABB1YPositionString = to_string(tileColliders[0]->ownerObject->GlobalTransform().m12);
	//string AABBYString = "Base AABB1 y coords:	" + AABB1YPositionString;
	//const char* AABBY = AABBYString.c_str();
	//DrawText(AABBY, 20, 690, 20, RED);
};