#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Enemy.h"
#include <iostream>
#include "Vector3.h"
#include "Controller.h"

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
	objType = Enemy_Type;
	moveSpeed = _moveSpeed;
	movingRight = true;
	this->SetWeapon(startingWeapon); // Laser by default
}

// This OnUpdate() overrides the one in the GameObject class
void Enemy::OnUpdate(float deltaTime, Controller& ctrlr) {
	// Always be sidescrolling, yo
	MoveSideways(deltaTime);
	
	// After 60 updates (approximately once a second) give the enemy a chance to fire
	if (shotTimer == 60) {
		ctrlr.ShootRandomly(*this, this->weaponEquipped);
		// Reset the counter
		shotTimer = 0;
	}

	// If the enemy doesn't fire, increment the shot timer (until it has another chance to fire)
	shotTimer++;	
};


void Enemy::MoveRight(float deltaTime) {
	// Get the local x and y of the x axis, multiply by time and speed
	// I think this effectively calculates the velocity (change in position over change in time)
	MyVector3 facing = MyVector3(
		this->LocalTransform().m00,
		this->LocalTransform().m10,
		0)
		* deltaTime
		* this->moveSpeed;

	// Move the object right (positive x facing) to the extent set by the facing vector
	this->Translate(facing.x, facing.y);
};

void Enemy::MoveLeft(float deltaTime) {
	// Get the local x and y of the x axis, multiply by time and speed
	// I think this effectively calculates the velocity (change in position over change in time)
	MyVector3 facing = MyVector3(
		this->LocalTransform().m00,
		this->LocalTransform().m10,
		0)
		* deltaTime
		* this->moveSpeed;

	// Move the object left (negative x facing) to the extent set by the facing vector
	this->Translate(-facing.x, facing.y);
};


void Enemy::MoveSideways(float deltaTime) {
	// Program screen size
	// Set these as a shared pointer for all classes to use!
	static const int leftSideOfScreen = 0;
	static const int rightSideOfScreen = 1080;

	int screenHeight = 720;

	if (this->movingRight && this->GlobalTransform().m02 < rightSideOfScreen) {
		MoveRight(deltaTime);
	}

	// If the ship is moving to the right and HAS hit the edge of the screen...
	if (this->movingRight && this->GlobalTransform().m02 >= rightSideOfScreen) {
		// cease the trigger to keep moving right
		this->movingRight = false;
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
		MoveRight(deltaTime);
	}
}