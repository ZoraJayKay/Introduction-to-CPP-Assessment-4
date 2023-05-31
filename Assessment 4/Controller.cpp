#pragma once

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
Controller::Controller() {
	std::cout << "---Default Controller constructor---" << endl;
};

// Overloaded constructor to permit accessing the hierarchy of parent/child objects
Controller::Controller(Game& gme) {
	std::cout << "---Overloaded Controller constructor---" << endl;
	*g = gme;
	weaponReloaded = true;
};

// Destructor
Controller::~Controller() {
	delete g;
	g = nullptr;
};


// A function to conditionally move the player based on keystrokes
void Controller::MoveSideways(GameObject& player, float deltaTime) {
	// If the player presses D or the right arrow key...
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		isMoving = true;
		// Increase accelerate to the right
		player.moveSpeed += player.moveAcceleration * deltaTime;

		if (player.moveSpeed > player.maxSpeed) {
			player.moveSpeed = player.maxSpeed;
		};
	}

	// If the player presses A or the left arrow key...
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		isMoving = true;
		// Increase accelerate to the left
		player.moveSpeed -= player.moveAcceleration * deltaTime;

		if (player.moveSpeed < -player.maxSpeed) {
			player.moveSpeed = -player.maxSpeed;
		};
	}

	// If the player hasn't pressed anything, start them decelerating
	if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)){
		// Set not moving
		isMoving = false;

		// Decelerate if player was moving right
		if (player.moveSpeed > 0) {
			player.moveSpeed += player.moveDrag * deltaTime;

			if (player.moveSpeed < 0) {
				player.moveSpeed = 0;
			}
		}

		// Decelerate if player was moving left
		if (player.moveSpeed < 0){
			player.moveSpeed -= player.moveDrag * deltaTime;

			if (player.moveSpeed > 0) {
				player.moveSpeed = 0;
			}
		}
	}

	// Move the player each frame according to its current acceleration
	if (isMoving = true) {
		MyVector3 facing = MyVector3(
			player.LocalTransform().m00,
			player.LocalTransform().m10,
			0)
			* deltaTime
			* player.moveSpeed;

		// Move the object forward to the extent set by the facing vector
		player.Translate(facing.x, facing.y);
	}
};

// Shoot the weapon if the spacebar or left mouse button is pressed and the weapon is ready to fire
void Controller::Shoot(GameObject& player, GameObject::weaponType weaponEquipped) {
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(0)) {
		if (weaponReloaded == true) {
			InstantiatePlayerAttack(player, weaponEquipped);
			shotTimer = 0;
			weaponReloaded = false;
		}
	}
}

// A function to let enemies fire at the player (see Enemy class OnUpdate() for what triggers this function)
void Controller::ShootRandomly(GameObject& enemy, GameObject::weaponType weaponEquipped) {
	bool willAttack = false;  
	int attackChance = GetRandomValue(0, 2);	// Give the enemy a 1 in 3 chance of firing per update
	
	switch (attackChance)
	{
	case 0: break;
	case 1: break;
	case 2: InstantiateEnemyAttack(enemy, weaponEquipped);
	}
};

void Controller::InstantiatePlayerAttack(GameObject& player, GameObject::weaponType weaponEquipped) {
	// Instantiate a new object of the type of weapon equipped and tag the weapon as a friendly shot
	Weapon* newAttack = new Weapon(weaponEquipped, player.Friendly_Projectile_Type);
	// Play a sound
	PlaySound(newAttack->laser_01);
	// Create the new attack a sprite
	SpriteObject* weaponSpritePtr = new SpriteObject();
	// Load the attack sprite a texture
	weaponSpritePtr->Load(newAttack->playerLaserAttackFileName);
	// Set the start position of the attack in the centre of the attacker's width and in front of their ship
	weaponSpritePtr->SetPosition(-weaponSpritePtr->Width() / 2, -weaponSpritePtr->Height() / 4);
	// Parent the attack object to its sprite object
	newAttack->AddChild(*weaponSpritePtr);
	// Copy the attacker's ship's global transform
	newAttack->CopyTransform(player);
	// Make the new attack a root object of the game class instance
	g->AddRootObject(*newAttack);
};


void Controller::InstantiateEnemyAttack(GameObject& enemy, GameObject::weaponType weaponEquipped) {
	// Instantiate a new object of the type of weapon equipped and tag the weapon as an enemy shot
	Weapon* newAttack = new Weapon(weaponEquipped, enemy.Enemy_Projectile_Type);
	// Play a sound
	PlaySound(newAttack->laser_02);
	// Create the new attack a sprite
	SpriteObject* weaponSpritePtr = new SpriteObject();
	// Load the attack sprite a texture
	weaponSpritePtr->Load(newAttack->enemyLaserAttackFileName);
	// Rotate the texture 180 degrees
	weaponSpritePtr->SetRotate(PI);
	// Set the start position of the attack in the centre of the attacker's width and in front of their ship
	weaponSpritePtr->SetPosition(-weaponSpritePtr->Width() / 2, weaponSpritePtr->Height() * 4);
	// Parent the attack object to its sprite object
	newAttack->AddChild(*weaponSpritePtr);
	// Copy the attacker's ship's global transform
	newAttack->CopyTransform(enemy);
	// Make the new attack a root object of the game class instance
	g->AddRootObject(*newAttack);
};