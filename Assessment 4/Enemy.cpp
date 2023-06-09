#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Enemy.h"
#include <iostream>
#include "Vector3.h"
#include "Controller.h"
#include "AABB.h"

// default constructor
Enemy::Enemy() {};


// default destructor
Enemy::~Enemy()
{

}

// overloaded constructor for speed and weapon of the enemy
Enemy::Enemy(int _moveSpeed, GameObject::weaponType startingWeapon)
{		
	std::cout << "---Enemy constructor---" << std::endl;
	moveSpeed = _moveSpeed;
	movingRight = true;
	this->SetWeapon(startingWeapon); // Laser by default
	shotTimer = 0;
	advanceTracker = 0;
	!reachedEarth;
	colliderPtr->ownerObject = this;
	this->objType = Enemy_Type;
}

// This OnUpdate() overrides the one in the GameObject class
void Enemy::OnUpdate(float deltaTime, Controller& ctrlr) {
	// Always be sidescrolling, yo
	//MoveSideways(deltaTime);
	
	// When the shot timer * delta time = 1 (approximately once a second) give the enemy a chance to fire
	if (shotTimer * deltaTime>= 1) {
		ctrlr.ShootRandomly(*this, this->weaponEquipped);
		// Reset the counter
		shotTimer = 0;
	}

	else {
		// If the enemy doesn't fire, increment the shot timer (until it has another chance to fire)
		shotTimer++;
	}
	
	// Implement an end to the game if the enemy advances 20 times?
	if (advanceTracker >= 20) {
		reachedEarth;
	}
};


void Enemy::MoveRight(float deltaTime) {
	// Get the local x and y of the x axis, multiply by time and speed
	// I think this effectively calculates the velocity (change in position over change in time)
	MyVector3 facing = MyVector3(
		this->LocalTransform().m00,
		this->LocalTransform().m11,
		0)
		* deltaTime
		* this->moveSpeed;

	// Move the object right (positive x facing) to the extent set by the facing vector
	this->Translate(facing.x, 0);
};

void Enemy::MoveLeft(float deltaTime) {
	// Get the local x and y of the x axis, multiply by time and speed
	// I think this effectively calculates the velocity (change in position over change in time)
	MyVector3 facing = MyVector3(
		this->LocalTransform().m00,
		this->LocalTransform().m11,
		0)
		* deltaTime
		* this->moveSpeed;

	// Move the object left (negative x facing) to the extent set by the facing vector
	this->Translate(-facing.x, 0);
};


void Enemy::MoveSideways(float deltaTime) {
	// Program screen size
	// Set these as a shared pointer for all classes to use!
	static const int leftSideOfScreen = 80;
	static const int rightSideOfScreen = 1000;

	int screenHeight = 720;

	if (this->movingRight && this->GlobalTransform().m02 < rightSideOfScreen) {
		MoveRight(deltaTime);
	}

	// If the ship is moving to the right and HAS hit the edge of the screen...
	if (this->movingRight && this->GlobalTransform().m02 >= rightSideOfScreen) {
		// cease the trigger to keep moving right
		this->movingRight = false;
		Advance(deltaTime);
		advanceTracker++;
		MoveLeft(deltaTime);
	}

	// If the ship is moving to the left and has not yet hit the edge of the screen...
	if (!this->movingRight && this->GlobalTransform().m02 > leftSideOfScreen) {
		MoveLeft(deltaTime);
	}

	// If the ship is moving to the left and HAS hit the edge of the screen...
	if (!this->movingRight && this->GlobalTransform().m02 <= leftSideOfScreen) {
		// turn on the trigger to move right
		this->movingRight = true;
		Advance(deltaTime);
		advanceTracker++;
		MoveRight(deltaTime);
	}
}

void Enemy::Advance(float deltaTime) {
	// Get the local x and y of the x axis, multiply by time and speed
	// Advance toward the player 4 time as fast as the enemy sidescrolls
	MyVector3 facing = MyVector3(
		this->LocalTransform().m00,
		this->LocalTransform().m11,
		0)
		* deltaTime
		* this->moveSpeed*4;

	// Move the object left (negative x facing) to the extent set by the facing vector
	this->Translate(0, facing.y);
};