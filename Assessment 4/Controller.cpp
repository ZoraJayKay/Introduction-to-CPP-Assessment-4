#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Controller.h"
#include "Vector3.h"
#include "Timer.h"
#include <iostream>
#include "SpriteObject.h"
#include "Game.h"

using namespace Utilities;

// Default constructor
Controller::Controller() {};

// Overloaded constructor to permit accessing the hierarchy of parent/child objects
Controller::Controller(Game& gme) {
	*g = gme;
};

// Destructor
Controller::~Controller() {
	/*delete g;
	g = nullptr;*/
};


// A function to conditionally move the player based on keystrokes
void Controller::MoveSideways(GameObject& obj, float deltaTime) {
	// If the player presses D or the right arrow key...
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		// Set the player to be moving
		isMoving;
		MyVector3 facing = MyVector3(
			obj.LocalTransform().m00,
			obj.LocalTransform().m10,
			0)		
			* deltaTime
			* obj.moveSpeed;

		// Move the object forward to the extent set by the facing vector
		obj.Translate(facing.x, facing.y);
	}

	// If the player presses A or the left arrow key...
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		// Set the player to be moving
		isMoving;
		MyVector3 facing = MyVector3(
			obj.LocalTransform().m00,
			obj.LocalTransform().m10,
			0)
			* deltaTime
			* obj.moveSpeed;

		// Move the object forward to the extent set by the facing vector
		obj.Translate(-facing.x, facing.y);
	}

	// Make sure that if the player has not pressed either left or right, I have a trigger that they are not moving
	if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)){
		!isMoving;
	}
};

// An attack function only for use by the player
//void Controller::Shoot(GameObject& obj, GameObject::weaponType weaponEquipped) {
//		if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(0)) {
//			// Shoot the weapon if the spacebar or left mouse button is pressed
//			InstantiatePlayerAttack(obj, weaponEquipped);
//		}
//}

void Controller::Shoot(GameObject& obj, GameObject::weaponType weaponEquipped) {
//void Controller::Shoot(GameObject& obj, int weaponEquipped) {
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(0)) {
		// Shoot the weapon if the spacebar or left mouse button is pressed
		InstantiatePlayerAttack(obj, weaponEquipped);
	}
}



// A function to let enemies fire at the player (see Enemy class OnUpdate() for what triggers this function)
void Controller::ShootRandomly(GameObject& obj, GameObject::weaponType weaponEquipped) {
	bool willAttack = false;  
	int attackChance = GetRandomValue(0, 2);	// Give the enemy a 1 in 3 chance of firing per update
	
	switch (attackChance)
	{
	case 0: break;
	case 1: break;
	case 2: InstantiateEnemyAttack(obj, weaponEquipped);
	}
};

void Controller::InstantiatePlayerAttack(GameObject& obj, GameObject::weaponType weaponEquipped) {
//void Controller::InstantiatePlayerAttack(GameObject& obj, int weaponEquipped) {
	// Instantiate a new object of the type of weapon equipped and tag the weapon as a friendly shot
	Weapon* newAttack = new Weapon(weaponEquipped, (GameObject::objectType)4);
	// Create the new attack a sprite
	SpriteObject* weaponSpritePtr = new SpriteObject();
	// Load the attack sprite a texture
	weaponSpritePtr->Load(newAttack->laserAttackFileName);
	// Set the start position of the attack in the centre of the attacker's width and in front of their ship
	weaponSpritePtr->SetPosition(-weaponSpritePtr->Width() / 2, -weaponSpritePtr->Height() / 4);
	// Parent the attack object to its sprite object
	newAttack->AddChild(*weaponSpritePtr);
	// Copy the attacker's ship's global transform
	newAttack->CopyTransform(obj);
	// Make the new attack a root object of the game class instance
	g->AddRootObject(*newAttack);
};


void Controller::InstantiateEnemyAttack(GameObject& obj, GameObject::weaponType weaponEquipped) {
	// Instantiate a new object of the type of weapon equipped and tag the weapon as an enemy shot
	Weapon* newAttack = new Weapon(weaponEquipped, (GameObject::objectType)5);
	// Create the new attack a sprite
	SpriteObject* weaponSpritePtr = new SpriteObject();
	// Load the attack sprite a texture
	weaponSpritePtr->Load(newAttack->laserAttackFileName);
	// Set the start position of the attack in the centre of the attacker's width and in front of their ship
	weaponSpritePtr->SetPosition(-weaponSpritePtr->Width() / 2, weaponSpritePtr->Height() * 2.25);
	// Parent the attack object to its sprite object
	newAttack->AddChild(*weaponSpritePtr);
	// Copy the attacker's ship's global transform
	newAttack->CopyTransform(obj);
	// Make the new attack a root object of the game class instance
	g->AddRootObject(*newAttack);
};