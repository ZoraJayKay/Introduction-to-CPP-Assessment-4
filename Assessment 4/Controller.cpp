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
};

Controller::~Controller() {
	// delete pointers
	// set pointer to null
};

// Conditionally move the player
void Controller::MoveSideways(GameObject& obj, float deltaTime) {
	if (IsKeyDown(KEY_D)) {
		MyVector3 facing = MyVector3(
			obj.LocalTransform().m00,
			obj.LocalTransform().m10,
			0)
			* deltaTime
			* obj.moveSpeed;

		// Move the object forward to the extent set by the facing vector
		obj.Translate(facing.x, facing.y);
	}

	if (IsKeyDown(KEY_A)) {
		MyVector3 facing = MyVector3(
			obj.LocalTransform().m00,
			obj.LocalTransform().m10,
			0)
			* deltaTime
			* obj.moveSpeed;

		// Move the object forward to the extent set by the facing vector
		obj.Translate(-facing.x, facing.y);
	}
};

void Controller::Shoot(GameObject::weaponType weaponEquipped) {
		if (IsKeyPressed(KEY_SPACE)) {
		// Instantiate a new object of the type of weapon equipped
		Weapon* newAttack = new Weapon(weaponEquipped);
		// Create the attack a sprite and make it the weapon's child
		SpriteObject* weaponSpritePtr = new SpriteObject();
		// Load the sprite a texture
		weaponSpritePtr->Load(newAttack->laserAttackFileName);
		// Set the start position of the attack
		weaponSpritePtr->SetPosition(weaponSpritePtr->Height() * 2.5f, -weaponSpritePtr->Width() / 2);
		// Parent the attack to its sprite
		newAttack->AddChild(*weaponSpritePtr);
		// Make the new attack a root object
		g->AddRootObject(*newAttack);
	}
}