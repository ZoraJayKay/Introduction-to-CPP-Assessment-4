#include "Enemy.h"
#include <iostream>
#include "Vector3.h"

// default constructor
Enemy::Enemy()
{		
	std::cout << "---Enemy constructor---" << std::endl;
	objType = Enemy_Type;
	moveSpeed = 250;
	movingRight = true;
}

// default destructor
Enemy::~Enemy()
{
	
}

void Enemy::OnUpdate(float deltaTime) {
	// Program screen size
	int leftSideOfScreen = 0;
	int rightSideOfScreen = 1080;
	int screenHeight = 720;

	// If the ship is moving to the right and has not yet hit the edge of the screen...
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
};


void Enemy::MoveRight(float deltaTime) {
	// Moving...
	MyVector3 facing = MyVector3(
		this->LocalTransform().m00,
		this->LocalTransform().m10,
		0)
		* deltaTime
		* this->moveSpeed;

	// Move the object right to the extent set by the facing vector
	this->Translate(facing.x, facing.y);
};

void Enemy::MoveLeft(float deltaTime) {
	// Moving...
	MyVector3 facing = MyVector3(
		this->LocalTransform().m00,
		this->LocalTransform().m10,
		0)
		* deltaTime
		* this->moveSpeed;

	// Move the object left to the extent set by the facing vector
	this->Translate(-facing.x, facing.y);
};