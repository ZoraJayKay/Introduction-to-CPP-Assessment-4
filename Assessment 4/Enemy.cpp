#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Enemy.h"
#include <iostream>
#include "Vector3.h"
#include "Controller.h"

// default constructor
Enemy::Enemy() {};

// overloaded constructor
Enemy::Enemy(int _moveSpeed, GameObject::weaponType startingWeapon)
{		
	std::cout << "---Enemy constructor---" << std::endl;
	objType = Enemy_Type;
	moveSpeed = _moveSpeed;
	movingRight = true;
	this->SetWeapon(startingWeapon); // Laser by default
}

// default destructor
Enemy::~Enemy()
{
	
}

void Enemy::OnUpdate(float deltaTime, Controller& ctrlr) {
	MoveSideways(deltaTime);
	
	// approximately once a second, give the enemy a chance to fire
	if (shotTimer == 60) {
		ctrlr.ShootRandomly(*this, this->weaponEquipped);
		shotTimer = 0;
	}

	// If the enemy doesn't fire, increment the shot timer (until it has another chance)
	shotTimer++;	
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


void Enemy::MoveSideways(float deltaTime) {
	// Program screen size
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

//void Enemy::ShootRandomly(GameObject& obj, GameObject::weaponType weaponEquipped) {
//	// Instantiate a new object of the type of weapon equipped
//	Weapon* newAttack = new Weapon(weaponEquipped);
//	// Create the new attack a sprite
//	SpriteObject* weaponSpritePtr = new SpriteObject();
//	// Load the attack sprite a texture
//	weaponSpritePtr->Load(newAttack->laserAttackFileName);
//	// Set the start position of the attack in the centre of the attacker's width and in front of their ship
//	weaponSpritePtr->SetPosition(-weaponSpritePtr->Width() / 2, -weaponSpritePtr->Height() / 4);
//	// Parent the attack object to its sprite object
//	newAttack->AddChild(*weaponSpritePtr);
//	// Copy the attacker's ship's global transform
//	newAttack->CopyTransform(obj);
//	// Make the new attack a root object of the game class instance
//	g->AddRootObject(*newAttack);
//};