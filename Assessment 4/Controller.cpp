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



Controller::Controller() {};
Controller::Controller(Game& gme) {
	*g = gme;


	// acceleration *= speed
	// My facing vector is my velocity vector
	// 
	// I need another vector for acceleration
	// 
	// 
	// velocity must be a Vector3, start it at (0, 0, 0)
	// velocity at a given moment = current velocity + (delta time * acceleration)
	// velocity += (delta time * acceleration)
	
	// position = delta time * velocity * 1/2 acceleration * delta time squared
	speedMin = 0;
	speedMax = 1;	
};

Controller::~Controller() {
	// delete pointers
	// set pointer to null
};


// Conditionally move the player
void Controller::MoveSideways(GameObject& obj, float deltaTime) {
	if (IsKeyDown(KEY_D)) {
		isMoving;
		// position = delta time * velocity * (acceleration * 0.5) * delta time^2
		MyVector3 facing = MyVector3(
			obj.LocalTransform().m00,
			obj.LocalTransform().m10,
			0)		
			* deltaTime
			* obj.moveSpeed;

			//MyVector3 facing2 = facing.Cross(*obj.acceleration);

		// Move the object forward to the extent set by the facing vector
		obj.Translate(facing.x, facing.y);
	}

	if (IsKeyDown(KEY_A)) {
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

	int h = 5;

	if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)){
		!isMoving;
	}
};

void Controller::Shoot(GameObject& obj, GameObject::weaponType weaponEquipped) {
		if (IsKeyPressed(KEY_SPACE)) {
			// Instantiate a new object of the type of weapon equipped
			Weapon* newAttack = new Weapon(weaponEquipped);
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
		}
}